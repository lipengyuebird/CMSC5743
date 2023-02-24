//
// Created by perye on 2/4/23.
//

#include "Im2col_Kernel.h"

#include <iostream>
#include <iomanip>

Im2col_Kernel::Im2col_Kernel(int K, int C, int R, int S) {
    this->K = K, this->C = C, this->R = R, this->S = S;
    this->kernelArray = new long * [K];
    for (int k = 0; k < K; ++k) {
        this->kernelArray[k] = new long [C * R * S];
    }

}

Im2col_Kernel * Im2col_Kernel::fromCanonical(Direct_Kernel * kernel) {
    Im2col_Kernel * im2_kernel = new Im2col_Kernel(kernel->K, kernel->C, kernel->R, kernel->S);
    for (int k = 0; k < kernel->K; ++k) {
        for (int c = 0; c < kernel->C; ++c) {
            for (int r = 0; r < kernel->R; ++r) {
                for (int s = 0; s < kernel->S; ++s) {
                    im2_kernel->kernelArray[k][kernel->R * kernel->S * c + kernel->S * r + s] = kernel->kernelArray[k][c][r][s];
                }
            }
        }
    }
    return im2_kernel;
}

void Im2col_Kernel::printArray() {
    for (int k = 0; k < K; ++k) {
        for (int i = 0; i < C * R * S; ++i) {
            std::cout << std::setw(12) << kernelArray[k][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void Im2col_Kernel::randInit() {
    for (int k = 0; k < K; ++k) {
        for (int i = 0; i < R * S; ++i) {
            kernelArray[k][i] = rand() >> 6;
        }
    }
}
