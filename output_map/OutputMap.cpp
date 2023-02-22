//
// Created by perye on 2/5/23.
//

#include "OutputMap.h"

#include <iostream>

OutputMap::OutputMap(int K, int P, int Q) {
    this->K = K, this->P = P, this->Q = Q;
    this->OutputArray = new long long ** [K];
    for (int k = 0; k < K; ++k) {
        this->OutputArray[k] = new long long * [P];
        for (int p = 0; p < P; ++p) {
            this->OutputArray[k][p] = new long long [Q];
        }
    }
}

void OutputMap::Print() {
    for (int k = 0; k < this->K; ++k) {
        for (int p = 0; p < P; ++p) {
            for (int q = 0; q < Q; ++q) {
                std::cout << OutputArray[k][p][q] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
}


