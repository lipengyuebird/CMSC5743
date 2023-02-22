//
// Created by perye on 2/5/23.
//

#ifndef IM2COL_OUTPUTMAP_H
#define IM2COL_OUTPUTMAP_H


class OutputMap {
public:
    OutputMap(int P, int Q);

    void Print();

    int P, Q;
    long long ** OutputArray;
};


#endif //IM2COL_OUTPUTMAP_H
