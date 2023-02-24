//
// Created by perye on 2/4/23.
//

#include "Im2col_FeatureMap.h"
#include "../acc_function/winograd/WinogradFunction.h"
#include "../acc_function/winograd/WinogradFunction_1D.h"

#include <iostream>
#include <iomanip>
#include <cassert>

Im2col_FeatureMap::Im2col_FeatureMap(int C, int H, int W, int R, int S) {
    this->C = C, this->H = H, this->W = W, this->R = R, this->S = S;
    this->P = H - R + 1;
    this->Q = W - S + 1;
    this->featureMapArray = new long * [P * Q];
    for (int c = 0; c < P * Q; ++c) {
        this->featureMapArray[c] = new long [C * R * S];
    }
}

Im2col_FeatureMap::~Im2col_FeatureMap() {
    for (int c = 0; c < C; ++c) {
        delete [] this->featureMapArray[c];
    }
    delete this->featureMapArray;
}

void Im2col_FeatureMap::randInit() {
    Direct_FeatureMap * C_FM = new Direct_FeatureMap(C, H, W);
    C_FM->randInit();
    for (int c = 0; c < C; ++c) {
        for (int h_s = 0; h_s < P; ++h_s) {
            for (int w_s = 0; w_s < Q; ++w_s) {
                for (int r = 0; r < R; ++r) {
                    for (int s = 0; s < S; ++s) {
                        featureMapArray[Q * h_s + w_s][R * S * c + S * r + s] =
                                C_FM->featureMapArray[c][h_s + r][w_s + s];
                    }
                }
            }
        }
    }
}

void Im2col_FeatureMap::printArray() {
    for (int j = 0; j < P * Q; ++j) {
        for (int k = 0; k < C * R * S; ++k) {
            std::cout << std::setw(12) << featureMapArray[j][k] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Im2col_FeatureMap * Im2col_FeatureMap::fromCanonical(Direct_FeatureMap * direct_featureMap, int R, int S) {
    assert(R <= direct_featureMap->H); assert(S <= direct_featureMap->W);
    int C = direct_featureMap->C, H = direct_featureMap->H, W = direct_featureMap->W;
    int P = H - R + 1;
    int Q = W - S + 1;
    Im2col_FeatureMap * Im2_FM = new Im2col_FeatureMap(C, H, W, R, S);
    for (int c = 0; c < C; ++c) {
        for (int h_s = 0; h_s < P; ++h_s) {
            for (int w_s = 0; w_s < Q; ++w_s) {
                for (int r = 0; r < R; ++r) {
                    for (int s = 0; s < S; ++s) {
                        Im2_FM->featureMapArray[Q * h_s + w_s][R * S * c + S * r + s] =
                                direct_featureMap->featureMapArray[c][h_s + r][w_s + s];
                    }
                }
            }
        }
    }
    return Im2_FM;
}

OutputMap *Im2col_FeatureMap::conv(Im2col_Kernel * im2_kernel) {
    int K = im2_kernel->K;
    OutputMap * outputMap = new OutputMap(K, P, Q);
    for (int k = 0; k < K; ++k) {
        for (int h_s = 0; h_s < P; ++h_s) {
            for (int w_s = 0; w_s < Q; ++w_s) {
                for (int i = 0; i < C * R * S; ++i) {
                    outputMap->outputArray[k][h_s][w_s] +=
                            this->featureMapArray[Q * h_s + w_s][i] * im2_kernel->kernelArray[k][i];
                }
            }
        }
    }
    return outputMap;
}

OutputMap *Im2col_FeatureMap::conv(Im2col_Kernel *im2_kernel, AcceleratorFunction * accFunction) {
    assert(C == im2_kernel->C);
    if (nullptr == accFunction) {
        return conv(im2_kernel);
    } else if (auto * func = dynamic_cast<WinogradFunction_1D*>(accFunction)) {
        return conv_winograd_1D(im2_kernel, func);
    }
    return conv(im2_kernel);
}

OutputMap *Im2col_FeatureMap::conv_winograd_1D(Im2col_Kernel *im2_kernel, WinogradFunction_1D *func) {
    int K = im2_kernel->K;
    if (func->getR() != R) {
        std::cerr << "Will not use specified Winograd function as its size does not match your kernel. " <<
        "Winograd: F(" << func->getM() << ", " << func->getR() << "). " <<
        "Kernel size: " << K << " * " << R << " * "  << S << ',' << std::endl;
        return conv(im2_kernel);
    }
    OutputMap * outputMap = new OutputMap(K, P, Q);
    for (int k = 0; k < K; ++k) {
        int row = 0;
        for (; row < P * Q - (func->getM() - 1); row += func->getM()) {
            int outputRowIdx1 = row / P;
            int outputColIdx1 = row - P * outputRowIdx1;
            int outputRowIdx2 = outputColIdx1 == P? outputRowIdx1 + 1: outputRowIdx1;
            int outputColIdx2 = outputColIdx1 == P? 0: outputColIdx1 + 1;
            int col = 0;
            for (; col < C * R * S - (func->getR() - 1); col += func->getR()) {
                long long * outputPtrArray[2] = {
                        &(outputMap->outputArray[k][outputRowIdx1][outputColIdx1]),
                        &(outputMap->outputArray[k][outputRowIdx2][outputColIdx2])
                };
                (*func)(this->featureMapArray, im2_kernel->kernelArray[k],
                        row, col, outputPtrArray);
            }
            for (; col < C * R * S; ++col) {
                outputMap->outputArray[k][outputRowIdx1][outputColIdx1] +=
                        this->featureMapArray[row][col] * im2_kernel->kernelArray[k][col];
                outputMap->outputArray[k][outputRowIdx2][outputColIdx2] +=
                        this->featureMapArray[row + 1][col] * im2_kernel->kernelArray[k][col];
            }
        }
        for (; row < P * Q; ++row) {
            int outputRowIdx = row / P;
            int outputColIdx = row - P * outputRowIdx;
            for (int col = 0; col < C * R * S; ++col) {
                outputMap->outputArray[k][outputRowIdx][outputColIdx] +=
                        this->featureMapArray[row][col] * im2_kernel->kernelArray[k][col];
            }
        }
    }
    return outputMap;
}
