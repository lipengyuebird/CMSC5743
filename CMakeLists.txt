cmake_minimum_required(VERSION 3.24)
project(Im2col)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(Im2col main.cpp kernel/DirectKernel.cpp feature_map/DirectFeatureMap.cpp feature_map/DirectFeatureMap.h feature_map/FeatureMap.h feature_map/Im2colFeatureMap.cpp feature_map/Im2colFeatureMap.h kernel/Im2colKernel.cpp kernel/Im2colKernel.h output_map/OutputMap.cpp output_map/OutputMap.h util/GetTime.h acc_function/winograd/WinogradFunction.h acc_function/winograd/WinogradFunction_1D.h acc_function/winograd/WinogradFunction_1D.cpp acc_function/AcceleratorFunction.h acc_function/strassen/StrassenFunction.h acc_function/strassen/StrassenFunction.h acc_function/strassen/StrassenFunction.h acc_function/strassen/StrassenFunction.h)
