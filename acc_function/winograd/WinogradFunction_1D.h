//
// Created by perye on 2/23/23.
//

#ifndef IM2COL_WINOGRADFUNCTION_1D_H
#define IM2COL_WINOGRADFUNCTION_1D_H


#include "WinogradFunction.h"

class WinogradFunction_1D: public WinogradFunction {
public:

    WinogradFunction_1D(int m, int r);

    [[nodiscard]] int getM() const;
    [[nodiscard]] int getR() const;

    void operator()(long ** IM2_FM_Array, long * IM2_K_Array, int Row_Idx, int Col_Idx, long long int ** Output_Ptr_Array) override;

private:
    int m, r;

    void winograd_2_3(long ** im2_featureMapArray, long * im2_kernelArray, int rowIdx, int colIdx, long long int ** outputPtrArray);
};


#endif //IM2COL_WINOGRADFUNCTION_1D_H
