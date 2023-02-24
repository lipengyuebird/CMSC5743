//
// Created by perye on 2/5/23.
//

#include "OutputMap.h"

#include <iostream>

OutputMap::OutputMap(int K, int P, int Q) {
    this->K = K, this->P = P, this->Q = Q;
    this->outputArray = new long long ** [K];
    for (int k = 0; k < K; ++k) {
        this->outputArray[k] = new long long * [P];
        for (int p = 0; p < P; ++p) {
            this->outputArray[k][p] = new long long [Q];
        }
    }
}

void OutputMap::print() {
    for (int k = 0; k < this->K; ++k) {
        for (int p = 0; p < P; ++p) {
            for (int q = 0; q < Q; ++q) {
                std::cout << outputArray[k][p][q] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
}


