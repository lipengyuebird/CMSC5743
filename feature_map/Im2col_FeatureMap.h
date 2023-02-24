//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_IM2COL_FEATUREMAP_H
#define LAB1_CODE_IM2COL_FEATUREMAP_H


#include "FeatureMap.h"
#include "Direct_FeatureMap.h"
#include "../kernel/Im2col_Kernel.h"
#include "../acc_function/AcceleratorFunction.h"
#include "../acc_function/winograd/WinogradFunction_1D.h"

class Im2col_FeatureMap: public FeatureMap{
public:
    Im2col_FeatureMap(int C, int H, int W, int R, int S);
    ~Im2col_FeatureMap();
    Im2col_FeatureMap static * fromCanonical(Direct_FeatureMap * direct_featureMap, int R, int S);

    void randInit();
    void printArray() override;

    OutputMap * conv(Im2col_Kernel * im2_kernel);
    OutputMap * conv(Im2col_Kernel * im2_kernel, AcceleratorFunction * accFunction);

    int R, S, P, Q;
    long ** featureMapArray;
private:
    OutputMap * conv_winograd_1D(Im2col_Kernel * im2_kernel, WinogradFunction_1D * func);

};


#endif //LAB1_CODE_IM2COL_FEATUREMAP_H
