//
// Created by perye on 2/4/23.
//

#include "Im2col_FeatureMap_3D.h"

#include <iostream>
#include <iomanip>
#include <cassert>

Im2col_FeatureMap_3D::Im2col_FeatureMap_3D(int C, int H, int W, int R, int S) {
    this->C = C, this->H = H, this->W = W, this->R = R, this->S = S;
    this->P = H - R + 1;
    this->Q = W - S + 1;
    this->FeatureMapArray = new long ** [C];
    for (int c = 0; c < C; ++c) {
        this->FeatureMapArray[c] = new long * [P * Q];
        for (int i = 0; i < P * Q; ++i) {
            this->FeatureMapArray[c][i] = new long [R * S];
        }
    }
}

Im2col_FeatureMap_3D::~Im2col_FeatureMap_3D() {
    for (int c = 0; c < C; ++c) {
        for (int i = 0; i < P * Q; ++i) {
            delete [] this->FeatureMapArray[c][i];
        }
        delete [] this->FeatureMapArray[c];
    }
    delete this->FeatureMapArray;
}

void Im2col_FeatureMap_3D::RandInit() {
    Direct_FeatureMap * C_FM = new Direct_FeatureMap(C, H, W);
    for (int c = 0; c < C; ++c) {
        for (int h_s = 0; h_s < P; ++h_s) {
            for (int w_s = 0; w_s < Q; ++w_s) {
                for (int r = 0; r < R; ++r) {
                    for (int s = 0; s < S; ++s) {
                        FeatureMapArray[c][Q * h_s + w_s][S * r + s] =
                                C_FM->FeatureMapArray[c][h_s + r][w_s + s];
                    }
                }
            }
        }
    }
}

void Im2col_FeatureMap_3D::PrintArray() {
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < P * Q; ++j) {
            for (int k = 0; k < R * S; ++k) {
                std::cout << std::setw(12) << FeatureMapArray[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Im2col_FeatureMap_3D * Im2col_FeatureMap_3D::FromCanonical(Direct_FeatureMap * C_FM, int R, int S) {
    assert(R <= C_FM->H); assert(S <= C_FM->W);
    int C = C_FM->C, H = C_FM->H, W = C_FM->W;
    int P = H - R + 1;
    int Q = W - S + 1;
    Im2col_FeatureMap_3D * Im2_FM = new Im2col_FeatureMap_3D(C, H, W, R, S);
    for (int c = 0; c < C; ++c) {
        for (int h_s = 0; h_s < P; ++h_s) {
            for (int w_s = 0; w_s < Q; ++w_s) {
                for (int r = 0; r < R; ++r) {
                    for (int s = 0; s < S; ++s) {
                        Im2_FM->FeatureMapArray[c][Q * h_s + w_s][S * r + s] =
                                C_FM->FeatureMapArray[c][h_s + r][w_s + s];
                    }
                }
            }
        }
    }
    return Im2_FM;
}

OutputMap *Im2col_FeatureMap_3D::conv(Im2col_Kernel_3D * Im2_K) {
    assert(C == Im2_K->C);
    OutputMap * O_M = new OutputMap(P, Q);
    for (int c = 0; c < C; ++c) {
        for (int h_s = 0; h_s < P; ++h_s) {
            for (int w_s = 0; w_s < Q; ++w_s) {
                for (int i = 0; i < R * S; ++i) {
                    O_M->OutputArray[h_s][w_s] += this->FeatureMapArray[c][Q * h_s + w_s][i] * Im2_K->KernelArray[c][i];
                }
            }
        }
    }
    return O_M;
}
