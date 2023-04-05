#include <iostream>

#include "feature_map/DirectFeatureMap.h"
#include "feature_map/Im2colFeatureMap.h"
#include "util/GetTime.h"
#include "acc_function/winograd/WinogradFunction_1D.h"
#include "feature_map/RegularSparseFeatureMap.h"
#include <npy.hpp>
#include <filesystem>


int main() {

    // =============== SET THE DATA PATH HERE ===============
    std::string path = R"(C:\Users\lipen\CLionProjects\CMSC5743\resources\pointcloud.npy)";

    const int C = 64, W = 64, H = 64;
    const int K = 64, R = 3, S = 3;

    // Set to true to view inner output
    const bool SHOW_OUTPUT = false;

    // Canonical feature map
    DirectFeatureMap<double_t> * directFeatureMap = DirectFeatureMap<double_t>::readNpy(path);
    if (SHOW_OUTPUT) directFeatureMap->printArray();

    // Im2col feature map
    auto * im2FeatureMap = Im2colFeatureMap<double_t>::fromCanonical(directFeatureMap, R, S);
    if (SHOW_OUTPUT) im2FeatureMap->printArray();

    auto sparseFeatureMap = RegularSparseFeatureMap<double>::fromCanonical(directFeatureMap, 3, 3);
    if (SHOW_OUTPUT) sparseFeatureMap->printArray();

    // Canonical kernel
    auto * directKernel = new DirectKernel(K, C, R, S);
    directKernel->randInit();

    if (SHOW_OUTPUT) directKernel->printArray();

    // Im2col kernel
    auto * im2Kernel = Im2colKernel::fromCanonical(directKernel);
    if (SHOW_OUTPUT) im2Kernel->printArray();

    double t0 = getTime();
    auto map1 = directFeatureMap->conv(directKernel);
    double t1 = getTime();
    auto map2 = im2FeatureMap->conv(im2Kernel);
    double t2 = getTime();
    auto map3 = im2FeatureMap->conv(im2Kernel, new WinogradFunction_1D<double>(2, 3));
    double t3 = getTime();
    auto map4 = sparseFeatureMap->conv(directKernel);
    double t4 = getTime();


    if (SHOW_OUTPUT) {
        map1->print();
        map2->print();
        map3->print();
        map4->print();
    }

    std::cout << "Direct conv: " << t1 - t0 << std::endl
              << "Im2col conv: " << t2 - t1 << std::endl
              << "Im2col conv with Winograd: " << t3 - t2 << std::endl
              << "Sparse conv: " << t4 - t3 << std::endl;

    // test
    for (int k = 0; k < map1->K; ++k) {
        for (int p = 0; p < map1->P; ++p) {
            for (int q = 0; q < map1->Q; ++q) {
                assert((map1->outputArray[k][p][q] - map4->outputArray[k][p][q]) < 1e-12);
            }
        }
    }

}
