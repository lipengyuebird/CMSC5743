//
// Created by perye on 2/22/23.
//

#ifndef IM2COL_GETTIME_H
#define IM2COL_GETTIME_H

#include <sys/time.h>

double getTime() {
    struct timeval tv{};
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + 1e-6 * tv.tv_usec;
}

#endif //IM2COL_GETTIME_H
