# Sparse Convolution

## Simple Usage
See `main.cpp`.

## Files and Directories
```
├── acc_function
│   ├── AcceleratorFunction.h
│   └── winograd
│       ├── WinogradFunction_1D.h
│       └── WinogradFunction.h
├── CMakeLists.txt
├── feature_map
│   ├── DirectFeatureMap.h
│   ├── FeatureMap.h
│   ├── Im2colFeatureMap.h
│   └── RegularSparseFeatureMap.h  // Regular sparse feature map (***HERE!***)
├── kernel
│   ├── DirectKernel.cpp
│   ├── DirectKernel.h
│   ├── Im2colKernel.cpp
│   ├── Im2colKernel.h
│   └── Kernel.h
├── main.cpp
├── output_map
│   └── OutputMap.h
├── resources
│   └── pointcloud.npy
└── util
    └── GetTime.h


```
## Result and Analysis
* Output Channel: 64  
![Screenshot from 2023-04-03 19-29-06.png](img/Screenshot%20from%202023-04-03%2019-29-06.png)
* Output Channel: 128  
![Screenshot from 2023-04-03 21-32-11.png](img/Screenshot%20from%202023-04-03%2021-32-11.png)
* Output Channel: 256  
![Screenshot from 2023-04-03 21-33-00.png](img/Screenshot%20from%202023-04-03%2021-33-00.png)
* Output Channel: 512  
![Screenshot from 2023-04-03 21-31-34.png](img/Screenshot%20from%202023-04-03%2021-31-34.png)  

Inference time is linearly corresponded to the amount of output channel because for every output  
channel the convolution operation repeats one more time.