//
// Created by perye on 2/4/23.
//

#ifndef LAB1_CODE_CANONICAL_FEATUREMAP_H
#define LAB1_CODE_CANONICAL_FEATUREMAP_H


#include <string>
#include <npy.hpp>

#include "FeatureMap.h"
#include "../output_map/OutputMap.h"
#include "../kernel/DirectKernel.h"


template<typename T>
class DirectFeatureMap: public FeatureMap {
public:

    DirectFeatureMap<T>(int C, int H, int W);
    ~DirectFeatureMap<T>();
    DirectFeatureMap<T> static * readNpy(std::string path);

    void randInit();
    void printArray() override;

    OutputMap * conv(DirectKernel * directKernel);

    T *** featureMapArray;
};

template<typename T>
DirectFeatureMap<T>::DirectFeatureMap(int C, int H, int W): FeatureMap(C, H, W) {
    this->featureMapArray = new T ** [C];
    for (int c = 0; c < C; ++c) {
        this->featureMapArray[c] = new T * [H];
        for (int h = 0; h < H; ++h) {
            this->featureMapArray[c][h] = new T [W];
        }
    }
}

template<typename T>
DirectFeatureMap<T>::~DirectFeatureMap() {
    for (int c = 0; c < C; ++c) {
        for (int h = 0; h < H; ++h) {
            delete [] this->featureMapArray[c][h];
        }
        delete [] this->featureMapArray[c];
    }
    delete [] this->featureMapArray;
}

template<typename T>
void DirectFeatureMap<T>::printArray() {

    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < H; ++j) {
            for (int k = 0; k < W; ++k) {
                std::cout << std::setw(12) << featureMapArray[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename T>
void DirectFeatureMap<T>::randInit() {
    for (int c = 0; c < C; ++c) {
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                this->featureMapArray[c][h][w] = rand() >> 10;
            }
        }
    }
}

template<typename T>
OutputMap *DirectFeatureMap<T>::conv(DirectKernel * directKernel) {
    int K = directKernel->K;
    int P = H - directKernel->R + 1;
    int Q = W - directKernel->S + 1;
    OutputMap * outputMap = new OutputMap(K, P, Q);
    for (int k = 0; k < K; ++k) {
        for (int c = 0; c < C; ++c) {
            int n = c;
            for (int h_s = 0; h_s < P; ++h_s) {
                for (int w_s = 0; w_s < Q; ++w_s) {
                    for (int r = 0; r < directKernel->R; ++r) {
                        for (int s = 0; s < directKernel->R; ++s) {
                            outputMap->outputArray[k][h_s][w_s] +=
                                    featureMapArray[c][h_s + r][w_s + s] * directKernel->kernelArray[k][n][r][s];
                        }
                    }
                }
            }
        }
    }
    return outputMap;
}

template<typename T>
DirectFeatureMap<T> *DirectFeatureMap<T>::readNpy(std::string path) {
    std::vector<unsigned long> shape;
    bool fortran_order;
    std::vector<T> dataVector;
    npy::LoadArrayFromNumpy(path, shape, fortran_order, dataVector);

    T * data = dataVector.data();
//    dataVector.clear();

    auto * map = new DirectFeatureMap<T>(shape[0], shape[1], shape[2]);
    map->featureMapArray = new T ** [map->C];
    for (int c = 0; c < map->C; ++c) {
        map->featureMapArray[c] = new T * [map->H];
        for (int j = 0; j < 64; ++j) {
            map->featureMapArray[c][j] = &(data[map->H * map->W * c + map->W * j]);
        }
    }
    return map;
}


#endif //LAB1_CODE_CANONICAL_FEATUREMAP_H
