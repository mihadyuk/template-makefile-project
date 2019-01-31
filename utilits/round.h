/*
 * round.h
 *
 *  Created on: Jan 31, 2019
 *      Author: amihadyuk
 */

#ifndef UTILITS_ROUND_H_
#define UTILITS_ROUND_H_

#include <stdint.h>
#include <assert.h>

// not finished yet
template<typename T>
T clz(T value) {
    T retval;
    switch (sizeof(T)) {
        case sizeof(uint8_t):
        case sizeof(uint16_t):
        case sizeof(uint32_t):
            retval = __builtin_clz(value);
        break;
        case sizeof(uint64_t):
            retval = __builtin_clzll(value);
        break;
        default:
            assert(false);
        break;
    };
    return retval;
}

template<typename T>
T roundToLowerPow2(T val) {
    if (val < 2)
        return val;
    val &= ~((1 << (sizeof(T)*8 - 1 - __builtin_clz(val))) - 1);
    return val;
}

template<typename T>
T roundToNearestPow2(T val) {
    if (val < 2)
        return val;
    T lower_digit = 1 << (sizeof(T)*8 - 2 - __builtin_clz(val));
    if (lower_digit & val)
        val = lower_digit << 2;
    else
        val &= ~((lower_digit << 1) - 1);
    return val;
}


#endif /* UTILITS_ROUND_H_ */
