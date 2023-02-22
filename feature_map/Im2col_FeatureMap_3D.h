//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_IM2COL_FEATUREMAP_3D_H
#define LAB1_CODE_IM2COL_FEATUREMAP_3D_H

#include "FeatureMap.h"
#include "Direct_FeatureMap.h"
#include "../kernel/Im2col_Kernel_3D.h"


class Im2col_FeatureMap_3D: public FeatureMap{
public:
    [[deprecated]]
    Im2col_FeatureMap_3D(int C, int H, int W, int R, int S);
    ~Im2col_FeatureMap_3D();
    [[deprecated]]
    Im2col_FeatureMap_3D static * FromCanonical(Direct_FeatureMap * C_FM, int R, int S);

    void RandInit();
    void PrintArray() override;

    OutputMap * conv(Im2col_Kernel_3D * Im2_K);

    int R, S, P, Q;
    long *** FeatureMapArray;
};


#endif //LAB1_CODE_IM2COL_FEATUREMAP_H
