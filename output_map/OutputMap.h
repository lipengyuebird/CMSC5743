//
// Created by perye on 2/5/23.
//

#ifndef IM2COL_OUTPUTMAP_H
#define IM2COL_OUTPUTMAP_H


template<typename T>
class OutputMap {
public:
    OutputMap<T>(int K, int P, int Q);

    void print();

    int K, P, Q;
    T *** outputArray;
};

template<typename T>
OutputMap<T>::OutputMap(int K, int P, int Q): K(K), P(P), Q(Q) {
    this->outputArray = new long long ** [K];
    for (int k = 0; k < K; ++k) {
        this->outputArray[k] = new long long * [P];
        for (int p = 0; p < P; ++p) {
            this->outputArray[k][p] = new long long [Q];
        }
    }
}

template<typename T>
void OutputMap<T>::print() {
    for (int k = 0; k < this->K; ++k) {
        for (int p = 0; p < P; ++p) {
            for (int q = 0; q < Q; ++q) {
                std::cout << outputArray[k][p][q] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
}


#endif //IM2COL_OUTPUTMAP_H
