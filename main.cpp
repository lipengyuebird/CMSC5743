#include <iostream>


#include "feature_map/Direct_FeatureMap.h"
#include "feature_map/Im2col_FeatureMap.h"
#include "util/GetTime.h"
#include "acc_function/winograd/WinogradFunction_1D.h"


int main() {

//    const int C = 3, H = 4, W = 4;
//    const int K = 3, R = 3, S = 3;

    // Under the settings below:
    // 1. Im2col approach does not show much difference compared to canonical one
    // 2. OpenMP and SIMD support greatly enhance the performance
    const int C = 3, H = 56, W = 56;
    const int K = 64, R = 3, S = 3;

    // Set to true to view inner output
    const bool SHOW_OUTPUT = false;

    // Canonical feature map
    auto * C_Map = new Direct_FeatureMap(C, H, W);
    C_Map->randInit();
    if (SHOW_OUTPUT) C_Map->printArray();

    // Im2col feature map
    auto * Im2_Map = Im2col_FeatureMap::fromCanonical(C_Map, R, S);
    if (SHOW_OUTPUT) Im2_Map->printArray();



    // Canonical kernel
    auto * C_Kernel = new Direct_Kernel(K, C, R, S);
    C_Kernel->randInit();
    if (SHOW_OUTPUT) C_Kernel->printArray();

    // Im2col kernel
    auto * Im2_Kernel = Im2col_Kernel::fromCanonical(C_Kernel);
    if (SHOW_OUTPUT) Im2_Kernel->printArray();

    double t0 = getTime();
    OutputMap * O_Map1 = C_Map->conv(C_Kernel);
    double t1 = getTime();
    OutputMap * O_Map2 = Im2_Map->conv(Im2_Kernel);
    double t2 = getTime();
    OutputMap * O_Map3 = Im2_Map->conv(Im2_Kernel, new WinogradFunction_1D(2, 3));
    double t3 = getTime();


    if (SHOW_OUTPUT) {
        O_Map1->print();
        O_Map3->print();
    }

    std::cout << "Direct conv: " << t1 - t0 << std::endl
    << "Im2col conv: " << t2 - t1 << std::endl
    << "Im2col conv with Winograd: " << t3 - t2 << std::endl;



}
