//
// Created by perye on 2/5/23.
//

#include "OutputMap.h"

#include <iostream>

OutputMap::OutputMap(int P, int Q) {
    this->P = P, this->Q = Q;
    this->OutputArray = new long long * [P];
    for (int p = 0; p < P; ++p) {
        this->OutputArray[p] = new long long [Q];
    }
}

void OutputMap::Print() {
    for (int p = 0; p < P; ++p) {
        for (int q = 0; q < Q; ++q) {
            std::cout << OutputArray[p][q] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


