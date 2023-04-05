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
class RegularSparseFeatureMap: public DirectFeatureMap<T> {
public:
    RegularSparseFeatureMap<T>(int C, int H, int W, int R, int S);
    virtual ~RegularSparseFeatureMap();
    RegularSparseFeatureMap<T> static * fromCanonical(DirectFeatureMap<T> * featureMap, int R, int S);

    void printArray() override;

    OutputMap<T> * conv(DirectKernel * directKernel) override;

    typedef std::tuple<int, int> pair_t;
    typedef std::tuple<int, int, int> triple_t;

    struct rbk_value {
        uint64_t in{};
        pair_t outIndex;
    };

private:
    int R, S, P, Q;
    std::vector<triple_t> hashIn; // (c, h, w)
    std::multimap<pair_t, rbk_value> rulebook;
};

template<typename T>
OutputMap<T> *RegularSparseFeatureMap<T>::conv(DirectKernel *directKernel) {
    assert(directKernel->C == this->C);
    auto outputMap = new OutputMap<T>(directKernel->K, this->P, this->Q);
    for (int k = 0; k < directKernel->K; ++k) {
        for (auto iter = rulebook.begin(); iter != rulebook.end(); ++iter) {
            triple_t in = this->hashIn[iter->second.in];
            outputMap->outputArray[k][std::get<0>(iter->second.outIndex)][std::get<1>(iter->second.outIndex)] +=
                    directKernel->kernelArray[k][std::get<0>(in)][std::get<0>(iter->first)][std::get<1>(iter->first)] *
                    this->featureMapArray[std::get<0>(in)][std::get<1>(in)][std::get<2>(in)];
        }
    }
    return outputMap;
}

template<typename T>
void RegularSparseFeatureMap<T>::printArray() {
    std::cout << hashIn.size();
    for (triple_t in: hashIn) {
        std::cout << std::get<0>(in) << ' ' << std::get<1>(in) << ' ' << std::get<2>(in) << std::endl;
    }
    std::cout << std::endl;
    for (auto iter = rulebook.begin(); iter != rulebook.end(); ++iter) {
        std::cout << '(' << std::get<0>(iter->first) << ", " << std::get<1>(iter->first) << ") "
                << iter->second.in << ' ' << std::get<0>(iter->second.outIndex)
                        << ' ' << std::get<1>(iter->second.outIndex) << std::endl;
    }
}

template<typename T>
RegularSparseFeatureMap<T> *RegularSparseFeatureMap<T>::fromCanonical(DirectFeatureMap<T> *featureMap, int R, int S) {
    auto * sparseFeatureMap =
            new RegularSparseFeatureMap<T>(featureMap->C, featureMap->H, featureMap->W, R, S);
    // TODO: use shared_ptr to avoid array being deleted
    sparseFeatureMap->featureMapArray = featureMap->featureMapArray;

    for (int h = 0; h < featureMap->H; ++h) {
        for (int w = 0; w < featureMap->W; ++w) {
            for (int c = 0; c < featureMap->C; ++c) {
                if (featureMap->featureMapArray[c][h][w] != 0) {
                    sparseFeatureMap->hashIn.push_back(RegularSparseFeatureMap::triple_t (c, h, w));
                    for (int r = std::max(0, R + h - featureMap->H); r < std::min(R, h + 1); ++r) {
                        for (int s = std::max(0, S + w - featureMap->W); s < std::min(S, w + 1); ++s) {
                            sparseFeatureMap->rulebook.insert({RegularSparseFeatureMap::pair_t(r, s),
                                                               RegularSparseFeatureMap::rbk_value{
                                                                       sparseFeatureMap->hashIn.size(),
                                                                       RegularSparseFeatureMap::pair_t(h - r, w - s)}});
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
    this->rulebook.clear();
}

template<typename T>
RegularSparseFeatureMap<T>::RegularSparseFeatureMap(int C, int H, int W, int R, int S) :
        DirectFeatureMap<T>(C, H, W), R(R), S(S), P(H - R + 1), Q(W - S + 1) {
}


#endif //IM2COL_REGULARSPARSEFEATUREMAP_H
