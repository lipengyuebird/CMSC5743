//
// Created by perye on 2/23/23.
//

#include <cassert>
#include <iostream>
#include "WinogradFunction_1D.h"

int WinogradFunction_1D::getM() const {
    return m;
}

int WinogradFunction_1D::getR() const {
    return r;
}

WinogradFunction_1D::WinogradFunction_1D(int m, int r) {
    this->m = m;
    this->r = r;
}

void WinogradFunction_1D::operator()(long **im2_featureMapArray, long *im2_kernelArray, int rowIdx, int colIdx,
                                     long long int **outputPtrArray) {
    if (2 == getM()) {
        if (3 == getR()) {
            winograd_2_3(im2_featureMapArray, im2_kernelArray, rowIdx, colIdx, outputPtrArray);
            return;
        }
    }

}

void WinogradFunction_1D::winograd_2_3(long **im2_featureMapArray, long *im2_kernelArray, int rowIdx, int colIdx,
                                       long long int **outputPtrArray) {

    // Make sure WinogradFunction does not excel the feature map the kernel.
    assert(im2_featureMapArray[rowIdx + 1][colIdx + 2]);
    assert(im2_kernelArray[colIdx + 2]);

    // find the address of the part of feature map used in calculation
    long * featureMapRow0 = & im2_featureMapArray[rowIdx][colIdx];
    long * featureMapRow1 = & im2_featureMapArray[rowIdx + 1][colIdx];

    // Make sure constraints of Winograd are met.
    assert(featureMapRow0[1] == featureMapRow1[0]);
    assert(featureMapRow0[2] == featureMapRow1[1]);

    // find the address of the part of kernel used in calculation.
    long * Kernel = & im2_kernelArray[colIdx];

    long long M1 = (featureMapRow0[0] - featureMapRow0[2]) * Kernel[0];
    // Use doubled M2 and M3 in case they are odd numbers.
    long long M2_twice = (featureMapRow0[1] + featureMapRow0[2]) * (Kernel[0] + Kernel[1] + Kernel[2]);
    long long M3_twice = (featureMapRow1[1] - featureMapRow1[0]) * (Kernel[0] - Kernel[1] + Kernel[2]);
    long long M4 = (featureMapRow1[0] - featureMapRow1[2]) * Kernel[2];

    (* outputPtrArray[0]) += (M1 + (M2_twice + M3_twice) / 2);
    (* outputPtrArray[1]) += ((M2_twice - M3_twice) / 2 - M4);
}
