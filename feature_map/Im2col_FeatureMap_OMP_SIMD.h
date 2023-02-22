//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_IM2COL_FEATUREMAP_OMP_SIMD_H
#define LAB1_CODE_IM2COL_FEATUREMAP_OMP_SIMD_H


#include "FeatureMap.h"
#include "Direct_FeatureMap.h"
#include "../kernel/Im2col_Kernel.h"

class Im2col_FeatureMap_OMP_SIMD: public FeatureMap{
public:
    Im2col_FeatureMap_OMP_SIMD(int C, int H, int W, int R, int S);
    ~Im2col_FeatureMap_OMP_SIMD();
    Im2col_FeatureMap_OMP_SIMD static * FromCanonical(Direct_FeatureMap * C_FM, int R, int S);

    void RandInit();
    void PrintArray() override;

    OutputMap * conv(Im2col_Kernel * Im2_K);

    int R, S, P, Q;
    long ** FeatureMapArray;
};


#endif //LAB1_CODE_IM2COL_FEATUREMAP_H
