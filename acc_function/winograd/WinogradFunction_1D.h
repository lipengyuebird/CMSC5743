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

    void operator()(long ** im2FeatureMapArray, long * im2KernelArray, int Row_Idx, int Col_Idx, long long int ** outputPtrArray) override;

private:
    int m, r;

    void winograd_2_3(long ** im2FeatureMapArray, long * im2KernelArray, int rowIdx, int colIdx, long long int ** outputPtrArray);
};


#endif //IM2COL_WINOGRADFUNCTION_1D_H
