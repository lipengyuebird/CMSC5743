//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_CANONICAL_FEATUREMAP_H
#define LAB1_CODE_CANONICAL_FEATUREMAP_H


#include "FeatureMap.h"
#include "../output_map/OutputMap.h"
#include "../kernel/DirectKernel.h"


class DirectFeatureMap: public FeatureMap {
public:

    DirectFeatureMap(int C, int H, int W);
    ~DirectFeatureMap();

    void randInit();
    void printArray() override;

    OutputMap * conv(DirectKernel * directKernel);

    long *** featureMapArray;
};


#endif //LAB1_CODE_CANONICAL_FEATUREMAP_H
