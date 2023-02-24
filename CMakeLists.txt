cmake_minimum_required(VERSION 3.24)
project(Im2col)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(Im2col main.cpp kernel/Direct_Kernel.cpp feature_map/Direct_FeatureMap.cpp feature_map/Direct_FeatureMap.h feature_map/FeatureMap.h feature_map/Im2col_FeatureMap.cpp feature_map/Im2col_FeatureMap.h kernel/Im2col_Kernel.cpp kernel/Im2col_Kernel.h output_map/OutputMap.cpp output_map/OutputMap.h util/GetTime.h acc_function/winograd/WinogradFunction.h acc_function/winograd/WinogradFunction_1D.h acc_function/winograd/WinogradFunction_1D.cpp acc_function/AcceleratorFunction.h acc_function/strassen/StrassenFunction.h acc_function/strassen/StrassenFunction.h acc_function/strassen/StrassenFunction.h acc_function/strassen/StrassenFunction.h)
