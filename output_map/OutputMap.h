//
// Created by perye on 2/5/23.
//

#ifndef IM2COL_OUTPUTMAP_H
#define IM2COL_OUTPUTMAP_H


class OutputMap {
public:
    OutputMap(int K, int P, int Q);

    void print();

    int K, P, Q;
    long long *** outputArray;
};


#endif //IM2COL_OUTPUTMAP_H
