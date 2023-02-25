//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_IM2COL_FEATUREMAP_OMP_H
#define LAB1_CODE_IM2COL_FEATUREMAP_OMP_H


#include "FeatureMap.h"
#include "DirectFeatureMap.h"
#include "../kernel/Im2colKernel.h"
#include "../acc_function/AcceleratorFunction.h"
#include "../acc_function/winograd/WinogradFunction_1D.h"

class Im2colFeatureMap_OMP: public FeatureMap{
public:
    Im2colFeatureMap_OMP(int C, int H, int W, int R, int S);
    ~Im2colFeatureMap_OMP();
    Im2colFeatureMap_OMP static * fromCanonical(DirectFeatureMap * directFeatureMap, int R, int S);

    void randInit();
    void printArray() override;

    OutputMap * conv(Im2colKernel * im2Kernel);
    OutputMap * conv(Im2colKernel * im2Kernel, AcceleratorFunction * accFunction);

    int R, S, P, Q;
    long ** featureMapArray;
private:
    OutputMap * conv_winograd_1D(Im2colKernel * im2Kernel, WinogradFunction_1D * func);

};


#endif //LAB1_CODE_IM2COL_FEATUREMAP_OMP_H
