//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_CANONICAL_FEATUREMAP_H
#define LAB1_CODE_CANONICAL_FEATUREMAP_H


#include "FeatureMap.h"
#include "../output_map/OutputMap.h"
#include "../kernel/Direct_Kernel.h"


class Direct_FeatureMap: public FeatureMap {
public:

    Direct_FeatureMap(int C, int H, int W);
    ~Direct_FeatureMap();

    void randInit();
    void printArray() override;

    OutputMap * conv(Direct_Kernel * directKernel);

    long *** featureMapArray;
};


#endif //LAB1_CODE_CANONICAL_FEATUREMAP_H
