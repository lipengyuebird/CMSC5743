//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_FEATUREMAP_H
#define LAB1_CODE_FEATUREMAP_H

class FeatureMap {
public:
    FeatureMap(int c, int h, int w) : C(c), H(h), W(w) {}

    virtual void printArray() = 0;
    int C, H, W;
};





#endif //LAB1_CODE_FEATUREMAP_H
