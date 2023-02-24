//
// Created by perye on 2/23/23.
//

#ifndef IM2COL_WINOGRADFUNCTION_H
#define IM2COL_WINOGRADFUNCTION_H


#include "../AcceleratorFunction.h"

class WinogradFunction: public AcceleratorFunction {
public:
    /**
     * Base Winograd function.
     * @param im2FmArray Feature map array based on Im2col.
     * @param im2KernelArray Kernel array based on Im2col.
     * @param rowIdx Starting row index.
     * @param colIdx Starting column index.
     * @param outputPtrArray Pointer array of output values whose length may differs according to what Winograd kernel is used.
     */
    virtual void operator()(long ** im2FmArray, long * im2KernelArray, int rowIdx, int colIdx, long long int ** outputPtrArray) = 0;
protected:
    WinogradFunction() = default;
    ~WinogradFunction() override = default;
};


#endif //IM2COL_WINOGRADFUNCTION_H
