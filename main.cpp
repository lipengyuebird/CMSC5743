#include <iostream>


#include "feature_map/Direct_FeatureMap.h"
#include "feature_map/Im2col_FeatureMap.h"
#include "util/GetTime.h"


int main() {

//    const int C = 3, H = 4, W = 4;
//    const int R = 3, S = 3;

    // Under the settings below:
    // 1. Im2col approach does not show much difference compared to canonical one
    // 2. OpenMP and SIMD support greatly enhance the performance
    const int C = 3, H = 128, W = 128;
    const int R = 64, S = 64;

    // Set to true to view inner output
    const bool SHOW_OUTPUT = false;

    // Canonical feature map
    auto * C_Map = new Direct_FeatureMap(C, H, W);
    C_Map->RandInit();
    if (SHOW_OUTPUT) C_Map->PrintArray();

    // Im2col feature map
    auto * Im2_Map = Im2col_FeatureMap::FromCanonical(C_Map, R, S);
    if (SHOW_OUTPUT) Im2_Map->PrintArray();



    // Canonical kernel
    auto * C_Kernel = new Direct_Kernel(1, C, R, S);
    C_Kernel->RandInit();
    if (SHOW_OUTPUT) C_Kernel->PrintArray();

    // Im2col kernel
    auto * Im2_Kernel = Im2col_Kernel::FromCanonical(C_Kernel);
    if (SHOW_OUTPUT) Im2_Kernel->PrintArray();

    double t0 = get_time();
    OutputMap * O_Map1 = C_Map->conv(C_Kernel);
    double t2 = get_time();
    OutputMap * O_Map3 = Im2_Map->conv(Im2_Kernel);
    double t3 = get_time();


    if (SHOW_OUTPUT) {
        O_Map1->Print();
        O_Map3->Print();
    }

    std::cout << "Direct conv: " << t2 - t0 << std::endl
    << "Im2col conv: " << t3 - t2 << std::endl;



}
