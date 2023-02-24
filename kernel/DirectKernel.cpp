//
// Created by perye on 2/4/23.
//

#include "DirectKernel.h"

#include <iostream>
#include <iomanip>

DirectKernel::DirectKernel(int K, int C, int R, int S) {
    this->K = K, this->C = C, this->R = R, this->S = S;
    this->kernelArray = new long *** [K];
    for (int k = 0; k < K; ++k) {
        this->kernelArray[k] = new long ** [C];
        for (int c = 0; c < C; ++c) {
            this->kernelArray[k][c] = new long * [R];
            for (int r = 0; r < R; ++r) {
                this->kernelArray[k][c][r] = new long [S];
            }
        }
    }
}

DirectKernel::~DirectKernel() {
    for (int k = 0; k < K; ++k) {
        for (int c = 0; c < C; ++c) {
            for (int r = 0; r < R; ++r) {
                delete kernelArray[k][c][r];
            }
            delete kernelArray[k][c];
        }
        delete kernelArray[k];
    }
    delete kernelArray;
}

void DirectKernel::printArray() {
    for (int k = 0; k < K; ++k) {
        for (int c = 0; c < C; ++c) {
            for (int r = 0; r < R; ++r) {
                for (int s = 0; s < S; ++s) {
                    std::cout << std::setw(12) << kernelArray[k][c][r][s] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void DirectKernel::randInit() {
    for (int k = 0; k < K; ++k) {
        for (int c = 0; c < C; ++c) {
            for (int r = 0; r < R; ++r) {
                for (int s = 0; s < S; ++s) {
                    kernelArray[k][c][r][s] = rand() >> 10;
                }
            }
        }
    }
}


