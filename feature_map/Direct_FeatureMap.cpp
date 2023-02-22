//
// Created by perye on 2/4/23.
//

#include "Direct_FeatureMap.h"

#include <iostream>
#include <iomanip>

Direct_FeatureMap::Direct_FeatureMap(int C, int H, int W) {
    this->C = C, this->H = H, this->W = W;
    this->FeatureMapArray = new long ** [C];
    for (int c = 0; c < C; ++c) {
        this->FeatureMapArray[c] = new long * [H];
        for (int h = 0; h < H; ++h) {
            this->FeatureMapArray[c][h] = new long [W];
        }
    }
}

Direct_FeatureMap::~Direct_FeatureMap() {
    for (int c = 0; c < C; ++c) {
        for (int h = 0; h < H; ++h) {
            delete [] this->FeatureMapArray[c][h];
        }
        delete [] this->FeatureMapArray[c];
    }
    delete this->FeatureMapArray;
}

void Direct_FeatureMap::PrintArray() {

    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < H; ++j) {
            for (int k = 0; k < W; ++k) {
                std::cout << std::setw(12) << FeatureMapArray[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Direct_FeatureMap::RandInit() {
    for (int c = 0; c < C; ++c) {
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                this->FeatureMapArray[c][h][w] = rand() >> 4;
            }
        }
    }
}

OutputMap *Direct_FeatureMap::conv(Direct_Kernel * C_K) {
    int P = H - C_K->R + 1;
    int Q = W - C_K->S + 1;
    OutputMap * O_M = new OutputMap(P, Q);
    for (int c = 0; c < C; ++c) {
        int n = c;
        for (int h_s = 0; h_s < P; ++h_s) {
            for (int w_s = 0; w_s < Q; ++w_s) {
                for (int r = 0; r < C_K->R; ++r) {
                    for (int s = 0; s < C_K->R; ++s) {
                        O_M->OutputArray[h_s][w_s] += FeatureMapArray[c][h_s + r][w_s + s] * C_K->KernelArray[n][r][s];
                    }
                }
            }
        }
    }
    return O_M;
}
