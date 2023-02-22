//
// Created by perye on 2/4/23.
//

#include "Direct_Kernel.h"

#include <iostream>
#include <iomanip>

Direct_Kernel::Direct_Kernel(int C, int R, int S) {
    this->C = C, this->R = R, this->S = S;
    this->KernelArray = new long ** [C];
    for (int c = 0; c < C; ++c) {
        this->KernelArray[c] = new long * [R];
        for (int r = 0; r < R; ++r) {
            this->KernelArray[c][r] = new long [S];
        }
    }
}

Direct_Kernel::~Direct_Kernel() {
    for (int r = 0; r < R; ++r) {
        delete KernelArray[r];
    }
    delete KernelArray;
}

void Direct_Kernel::PrintArray() {
    for (int c = 0; c < C; ++c) {
        for (int r = 0; r < R; ++r) {
            for (int s = 0; s < S; ++s) {
                std::cout << std::setw(12) << KernelArray[c][r][s] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Direct_Kernel::RandInit() {
    for (int c = 0; c < C; ++c) {
        for (int r = 0; r < R; ++r) {
            for (int s = 0; s < S; ++s) {
                KernelArray[c][r][s] = rand() >> 4;
            }
        }
    }
}


