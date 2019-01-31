/*
 * round.h
 *
 *  Created on: Jan 31, 2019
 *      Author: amihadyuk
 */

#ifndef UTILITS_ROUND_H_
#define UTILITS_ROUND_H_

#include <stdint.h>

template<typename T>
T roundToNearestPow2(T val) {
    if (val < 2)
        return val;
    val &= ~((1 << (sizeof(T)*8 - 1 - __builtin_clz(val))) - 1);
    return val;
}


#endif /* UTILITS_ROUND_H_ */
