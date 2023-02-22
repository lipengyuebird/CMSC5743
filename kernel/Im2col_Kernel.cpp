//
// Created by perye on 2/4/23.
//

#include "Im2col_Kernel.h"

#include <iostream>
#include <iomanip>

Im2col_Kernel::Im2col_Kernel(int K, int C, int R, int S) {
    this->K = K, this->C = C, this->R = R, this->S = S;
    this->KernelArray = new long * [K];
    for (int k = 0; k < K; ++k) {
        this->KernelArray[k] = new long [C * R * S];
    }

}

Im2col_Kernel * Im2col_Kernel::FromCanonical(Direct_Kernel * C_K) {
    Im2col_Kernel * Im2_K = new Im2col_Kernel(C_K->K, C_K->C, C_K->R, C_K->S);
    for (int k = 0; k < C_K->K; ++k) {
        for (int c = 0; c < C_K->C; ++c) {
            for (int r = 0; r < C_K->R; ++r) {
                for (int s = 0; s < C_K->S; ++s) {
                    Im2_K->KernelArray[k][C_K->R * C_K->S * c + C_K->S * r + s] = C_K->KernelArray[k][c][r][s];
                }
            }
        }
    }
    return Im2_K;
}

void Im2col_Kernel::PrintArray() {
    for (int k = 0; k < K; ++k) {
        for (int i = 0; i < C * R * S; ++i) {
            std::cout << std::setw(12) << KernelArray[k][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void Im2col_Kernel::RandInit() {
    for (int k = 0; k < K; ++k) {
        for (int i = 0; i < R * S; ++i) {
            KernelArray[k][i] = rand() >> 4;
        }
    }
}
