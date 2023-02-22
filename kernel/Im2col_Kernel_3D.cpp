//
// Created by perye on 2/4/23.
//

#include "Im2col_Kernel_3D.h"

#include <iostream>
#include <iomanip>


Im2col_Kernel_3D::Im2col_Kernel_3D(int C, int R, int S) {
    this->C = C, this->R = R, this->S = S;
    this->KernelArray = new long * [C];
    for (int c = 0; c < C; ++c) {
        this->KernelArray[c] = new long [R * S];
    }
}

Im2col_Kernel_3D * Im2col_Kernel_3D::FromCanonical(Direct_Kernel * C_K) {
    Im2col_Kernel_3D * Im2_K = new Im2col_Kernel_3D(C_K->C, C_K->R, C_K->S);
    for (int c = 0; c < C_K->C; ++c) {
        for (int r = 0; r < C_K->R; ++r) {
            for (int s = 0; s < C_K->S; ++s) {
                Im2_K->KernelArray[c][C_K->S * r + s] = C_K->KernelArray[c][r][s];
            }
        }
    }
    return Im2_K;
}

void Im2col_Kernel_3D::PrintArray() {
    for (int c = 0; c < C; ++c) {
        for (int i = 0; i < R * S; ++i) {
            std::cout << std::setw(12) << KernelArray[c][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Im2col_Kernel_3D::RandInit() {
    for (int c = 0; c < C; ++c) {
        for (int i = 0; i < R * S; ++i) {
            KernelArray[c][i] = rand() >> 4;
        }
    }
}
