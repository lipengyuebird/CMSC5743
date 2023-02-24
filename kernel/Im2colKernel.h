//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_IM2COL_KERNEL_H
#define LAB1_CODE_IM2COL_KERNEL_H


#include "Kernel.h"
#include "DirectKernel.h"

class Im2colKernel: public Kernel{
public:
    Im2colKernel(int K, int C, int R, int S);
    Im2colKernel static * fromCanonical(DirectKernel * kernel);

    void randInit();
    void printArray() override;

    long ** kernelArray;

};


#endif //LAB1_CODE_IM2COL_KERNEL_H
