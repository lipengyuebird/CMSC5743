//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_CANONICAL_KERNEL_H
#define LAB1_CODE_CANONICAL_KERNEL_H


#include "Kernel.h"

class Direct_Kernel: public Kernel{
public:
    Direct_Kernel(int K, int C, int R, int S);
    ~Direct_Kernel();
    void randInit();
    void printArray() override;

    long **** kernelArray;
};


#endif //LAB1_CODE_CANONICAL_KERNEL_H
