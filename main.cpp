#include <iostream>

#include "feature_map/DirectFeatureMap.h"
#include "feature_map/Im2colFeatureMap.h"
#include "util/GetTime.h"
#include "acc_function/winograd/WinogradFunction_1D.h"
#include <npy.hpp>


int main() {

    DirectFeatureMap<float> * directFeatureMap  = DirectFeatureMap<float>::readNpy("/Users/perye/CLionProjects/CMSC5743/resources/matrix_f4.npy");
    directFeatureMap->printArray();

//    const int C = 3, H = 56, W = 56;
//    const int K = 64, R = 3, S = 3;
//
//    // Set to true to view inner output
//    const bool SHOW_OUTPUT = false;
//
//    // Canonical feature map
//    auto * directFeatureMap = new DirectFeatureMap(C, H, W);
//    directFeatureMap->randInit();
//    if (SHOW_OUTPUT) directFeatureMap->printArray();
//
//    // Im2col feature map
//    auto * im2FeatureMap = Im2colFeatureMap::fromCanonical(directFeatureMap, R, S);
//    if (SHOW_OUTPUT) im2FeatureMap->printArray();
//
//    // Im2col feature map (OpenMP applied)
//    auto * im2FeatureMap_OMP = Im2colFeatureMap_OMP::fromCanonical(directFeatureMap, R, S);
//    if (SHOW_OUTPUT) im2FeatureMap_OMP->printArray();
//
//
//
//    // Canonical kernel
//    auto * directKernel = new DirectKernel(K, C, R, S);
//    directKernel->randInit();
//    if (SHOW_OUTPUT) directKernel->printArray();
//
//    // Im2col kernel
//    auto * im2Kernel = Im2colKernel::fromCanonical(directKernel);
//    if (SHOW_OUTPUT) im2Kernel->printArray();
//
//    double t0 = getTime();
//    OutputMap * map1 = directFeatureMap->conv(directKernel);
//    double t1 = getTime();
//    OutputMap * map2 = im2FeatureMap->conv(im2Kernel);
//    double t2 = getTime();
//    OutputMap * map3 = im2FeatureMap->conv(im2Kernel, new WinogradFunction_1D(2, 3));
//    double t3 = getTime();
//    OutputMap * map4 = im2FeatureMap_OMP->conv(im2Kernel, new WinogradFunction_1D(2, 3));
//    double t4 = getTime();
//
//
//    if (SHOW_OUTPUT) {
//        map1->print();
//        map2->print();
//        map3->print();
//        map4->print();
//    }
//
//    std::cout << "Direct conv: " << t1 - t0 << std::endl
//    << "Im2col conv: " << t2 - t1 << std::endl
//    << "Im2col conv with Winograd: " << t3 - t2 << std::endl
//    << "Im2col conv with Winograd (OpenMP enabled): " << t4 - t3 << std::endl;

}
