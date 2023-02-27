//
// Created by perye on 2/4/23.
//

#include "DirectFeatureMap.h"

#include <iostream>
#include <iomanip>

DirectFeatureMap::DirectFeatureMap(int C, int H, int W) {
    this->C = C, this->H = H, this->W = W;
    this->featureMapArray = new long ** [C];
    for (int c = 0; c < C; ++c) {
        this->featureMapArray[c] = new long * [H];
        for (int h = 0; h < H; ++h) {
            this->featureMapArray[c][h] = new long [W];
        }
    }
}

DirectFeatureMap::~DirectFeatureMap() {
    for (int c = 0; c < C; ++c) {
        for (int h = 0; h < H; ++h) {
            delete [] this->featureMapArray[c][h];
        }
        delete [] this->featureMapArray[c];
    }
    delete [] this->featureMapArray;
}

void DirectFeatureMap::printArray() {

    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < H; ++j) {
            for (int k = 0; k < W; ++k) {
                std::cout << std::setw(12) << featureMapArray[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void DirectFeatureMap::randInit() {
    for (int c = 0; c < C; ++c) {
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                this->featureMapArray[c][h][w] = rand() >> 10;
            }
        }
    }
}

OutputMap *DirectFeatureMap::conv(DirectKernel * directKernel) {
    int K = directKernel->K;
    int P = H - directKernel->R + 1;
    int Q = W - directKernel->S + 1;
    OutputMap * outputMap = new OutputMap(K, P, Q);
    for (int k = 0; k < K; ++k) {
        for (int c = 0; c < C; ++c) {
            int n = c;
            for (int h_s = 0; h_s < P; ++h_s) {
                for (int w_s = 0; w_s < Q; ++w_s) {
                    for (int r = 0; r < directKernel->R; ++r) {
                        for (int s = 0; s < directKernel->R; ++s) {
                            outputMap->outputArray[k][h_s][w_s] +=
                                    featureMapArray[c][h_s + r][w_s + s] * directKernel->kernelArray[k][n][r][s];
                        }
                    }
                }
            }
        }
    }
    return outputMap;
}
