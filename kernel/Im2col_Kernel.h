//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_IM2COL_KERNEL_H
#define LAB1_CODE_IM2COL_KERNEL_H


#include "Kernel.h"
#include "Direct_Kernel.h"

class Im2col_Kernel: public Kernel{
public:
    Im2col_Kernel(int K, int C, int R, int S);
    Im2col_Kernel static * fromCanonical(Direct_Kernel * kernel);

    void randInit();
    void printArray() override;

    long ** kernelArray;

};


#endif //LAB1_CODE_IM2COL_KERNEL_H
