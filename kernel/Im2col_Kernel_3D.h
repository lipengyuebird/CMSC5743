//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_IM2COL_KERNEL_3D_H
#define LAB1_CODE_IM2COL_KERNEL_3D_H

#include "Kernel.h"
#include "Direct_Kernel.h"

class Im2col_Kernel_3D: public Kernel{
public:
    [[deprecated]]
    Im2col_Kernel_3D(int C, int R, int S);
    [[deprecated]]
    Im2col_Kernel_3D static * FromCanonical(Direct_Kernel * C_K);

    void RandInit();
    void PrintArray() override;

    long ** KernelArray;

};


#endif //LAB1_CODE_IM2COL_KERNEL_H
