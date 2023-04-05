//
// Created by perye on 2/23/23.
//

#ifndef IM2COL_WINOGRADFUNCTION_1D_H
#define IM2COL_WINOGRADFUNCTION_1D_H


#include "WinogradFunction.h"

template<typename T>
class WinogradFunction_1D: public WinogradFunction<T> {
public:

    WinogradFunction_1D(int m, int r);

    [[nodiscard]] int getM() const;
    [[nodiscard]] int getR() const;

    void operator()(T ** im2FeatureMapArray, long * im2KernelArray, int rowIdx, int colIdx, T ** outputPtrArray) override;

private:
    int m, r;

    void winograd_2_3(T ** im2FeatureMapArray, long * im2KernelArray, int rowIdx, int colIdx, T ** outputPtrArray);
};

template<typename T>
int WinogradFunction_1D<T>::getM() const {
    return m;
}

template<typename T>
int WinogradFunction_1D<T>::getR() const {
    return r;
}

template<typename T>
WinogradFunction_1D<T>::WinogradFunction_1D(int m, int r) {
    this->m = m;
    this->r = r;
}

template<typename T>
void WinogradFunction_1D<T>::operator()(T **im2FeatureMapArray, long *im2KernelArray, int rowIdx, int colIdx,
                                        T **outputPtrArray) {
    if (2 == getM()) {
        if (3 == getR()) {
            winograd_2_3(im2FeatureMapArray, im2KernelArray, rowIdx, colIdx, outputPtrArray);
            return;
        }
    }

}

template<typename T>
void WinogradFunction_1D<T>::winograd_2_3(T **im2FeatureMapArray, long *im2KernelArray, int rowIdx, int colIdx,
                                          T **outputPtrArray) {

    // Make sure WinogradFunction does not excel the feature map the kernel.
    assert(&(im2FeatureMapArray[rowIdx + 1][colIdx + 2]) != nullptr);
    assert(im2KernelArray[colIdx + 2] || im2KernelArray[colIdx + 2] == 0);

    // find the address of the part of feature map used in calculation
    T * featureMapRow0 = & im2FeatureMapArray[rowIdx][colIdx];
    T * featureMapRow1 = & im2FeatureMapArray[rowIdx + 1][colIdx];

    // Make sure constraints of Winograd are met.
    assert(featureMapRow0[1] == featureMapRow1[0]);
    assert(featureMapRow0[2] == featureMapRow1[1]);

    // find the address of the part of kernel used in calculation.
    long * Kernel = & im2KernelArray[colIdx];

    T M1 = (featureMapRow0[0] - featureMapRow0[2]) * Kernel[0];
    // Use doubled M2 and M3 in case they are odd numbers.
    T M2_twice = (featureMapRow0[1] + featureMapRow0[2]) * (Kernel[0] + Kernel[1] + Kernel[2]);
    T M3_twice = (featureMapRow1[1] - featureMapRow1[0]) * (Kernel[0] - Kernel[1] + Kernel[2]);
    T M4 = (featureMapRow1[0] - featureMapRow1[2]) * Kernel[2];

    (* outputPtrArray[0]) += (M1 + (M2_twice + M3_twice) / 2);
    (* outputPtrArray[1]) += ((M2_twice - M3_twice) / 2 - M4);
}

#endif //IM2COL_WINOGRADFUNCTION_1D_H
