//
// Created by perye on 3/29/23.
//

#ifndef IM2COL_REGULARSPARSEFEATUREMAP_H
#define IM2COL_REGULARSPARSEFEATUREMAP_H

#include <map>
#include <vector>
#include "FeatureMap.h"
#include "DirectFeatureMap.h"


template<typename T>
class RegularSparseFeatureMap: public FeatureMap {
public:
    RegularSparseFeatureMap<T>(int C, int H, int W, int R, int S);
    virtual ~RegularSparseFeatureMap();
    RegularSparseFeatureMap<T> static * fromCanonical(DirectFeatureMap<T> * featureMap, int R, int S);

    void printArray() override;

    OutputMap<T> * conv(DirectKernel * directKernel);


    typedef std::tuple<int, int> pair_t;
    typedef std::tuple<int, int, int> triple_t;

    struct rbk_value {
        uint64_t in;
        pair_t outIndex;
    };

private:
    int R, S, P, Q;
    std::vector<triple_t> hashIn;
    std::vector<pair_t> hashOut;
    std::multimap<pair_t, rbk_value> rulebook;
};

template<typename T>
OutputMap<T> *RegularSparseFeatureMap<T>::conv(DirectKernel *directKernel) {
    return nullptr;
}

template<typename T>
void RegularSparseFeatureMap<T>::printArray() {

}

template<typename T>
RegularSparseFeatureMap<T> *RegularSparseFeatureMap<T>::fromCanonical(DirectFeatureMap<T> *featureMap, int R, int S) {
    auto * sparseFeatureMap =
            new RegularSparseFeatureMap<T>(featureMap->C, featureMap->H, featureMap->W, R, S);

    for (int h = 0; h < featureMap->H; ++h) {
        for (int w = 0; w < featureMap->W; ++w) {
            for (int c = 0; c < featureMap->C; ++c) {
                if (featureMap->featureMapArray[c][h][w] != 0) {
                    sparseFeatureMap->hashIn.push_back(RegularSparseFeatureMap::triple_t (c, h, w));
                    for (int r = std::max(0, R + h - featureMap->H); r < std::min(R, R - h); ++r) {
                        for (int s = std::max(0, S + w - featureMap->W); s < std::max(S, S - w); ++s) {
                            sparseFeatureMap->rulebook.insert({RegularSparseFeatureMap::pair_t(r, s),
                                                               RegularSparseFeatureMap::rbk_value{
                                                                       sparseFeatureMap->hashIn.size() - 1,
                                                                       RegularSparseFeatureMap::pair_t(w + r, h + s)}});
                        }
                    }
                }
            }
        }
    }
    return sparseFeatureMap;
}


template<typename T>
RegularSparseFeatureMap<T>::~RegularSparseFeatureMap() {
    this->hashIn.clear();
    this->hashOut.clear();
    this->rulebook.clear();
}

template<typename T>
RegularSparseFeatureMap<T>::RegularSparseFeatureMap(int C, int H, int W, int R, int S) :
        FeatureMap(C, H, W), R(R), S(S), P(H - R + 1), Q(W - S + 1) {
//    this->hashIn = new std::vector<pair_t>;
//    this->hashOut = new std::vector<pair_t>;
//    this->rulebook = new std::multimap<pair_t, rbk_value>;
}


#endif //IM2COL_REGULARSPARSEFEATUREMAP_H
