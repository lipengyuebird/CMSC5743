//
// Created by perye on 2/4/23.
//

#include "Im2col_FeatureMap.h"

#include <iostream>
#include <iomanip>
#include <cassert>

Im2col_FeatureMap::Im2col_FeatureMap(int C, int H, int W, int R, int S) {
    this->C = C, this->H = H, this->W = W, this->R = R, this->S = S;
    this->P = H - R + 1;
    this->Q = W - S + 1;
    this->FeatureMapArray = new long * [P * Q];
    for (int c = 0; c < P * Q; ++c) {
        this->FeatureMapArray[c] = new long [C * R * S];
    }
}

Im2col_FeatureMap::~Im2col_FeatureMap() {
    for (int c = 0; c < C; ++c) {
        delete [] this->FeatureMapArray[c];
    }
    delete this->FeatureMapArray;
}

void Im2col_FeatureMap::RandInit() {
    Direct_FeatureMap * C_FM = new Direct_FeatureMap(C, H, W);
    for (int c = 0; c < C; ++c) {
        for (int h_s = 0; h_s < P; ++h_s) {
            for (int w_s = 0; w_s < Q; ++w_s) {
                for (int r = 0; r < R; ++r) {
                    for (int s = 0; s < S; ++s) {
                        FeatureMapArray[Q * h_s + w_s][R * S * c + S * r + s] =
                                C_FM->FeatureMapArray[c][h_s + r][w_s + s];
                    }
                }
            }
        }
    }
}

void Im2col_FeatureMap::PrintArray() {
    for (int j = 0; j < P * Q; ++j) {
        for (int k = 0; k < C * R * S; ++k) {
            std::cout << std::setw(12) << FeatureMapArray[j][k] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Im2col_FeatureMap * Im2col_FeatureMap::FromCanonical(Direct_FeatureMap * C_FM, int R, int S) {
    assert(R <= C_FM->H); assert(S <= C_FM->W);
    int C = C_FM->C, H = C_FM->H, W = C_FM->W;
    int P = H - R + 1;
    int Q = W - S + 1;
    Im2col_FeatureMap * Im2_FM = new Im2col_FeatureMap(C, H, W, R, S);
    for (int c = 0; c < C; ++c) {
        for (int h_s = 0; h_s < P; ++h_s) {
            for (int w_s = 0; w_s < Q; ++w_s) {
                for (int r = 0; r < R; ++r) {
                    for (int s = 0; s < S; ++s) {
                        Im2_FM->FeatureMapArray[Q * h_s + w_s][R * S * c + S * r + s] =
                                C_FM->FeatureMapArray[c][h_s + r][w_s + s];
                    }
                }
            }
        }
    }
    return Im2_FM;
}

OutputMap *Im2col_FeatureMap::conv(Im2col_Kernel * Im2_K) {
    return conv(Im2_K, false);
}

OutputMap *Im2col_FeatureMap::conv(Im2col_Kernel *Im2_K, bool Winograd) {
    assert(C == Im2_K->C);
    int K = Im2_K->K;
    OutputMap * O_M = new OutputMap(K, P, Q);
    if (!Winograd) {
        for (int k = 0; k < K; ++k) {
            for (int h_s = 0; h_s < P; ++h_s) {
                for (int w_s = 0; w_s < Q; ++w_s) {
                    for (int i = 0; i < C * R * S; ++i) {
                        O_M->OutputArray[k][h_s][w_s] += this->FeatureMapArray[Q * h_s + w_s][i] * Im2_K->KernelArray[k][i];
                    }
                }
            }
        }
    } else {

    }
    return O_M;
}
