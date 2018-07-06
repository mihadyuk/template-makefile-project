/*
 * classesAggregateInit.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: Andrey
 */
#include "aggregateInitMain.h"
#include <stdio.h>

struct PlainStruct {
    int32_t  m_int32;
    uint16_t m_uint16;
};

typedef union {
    uint32_t m_val;
    struct {
        unsigned m_bit1:4;
        unsigned m_bit2:4;
        unsigned m_reserved:24;
    } bits;
} PlainUnion;


void aggregateInitMain() {

    PlainStruct plainStruct = {.m_int32 = -1, .m_uint16 = 2};
    printf("int32: %d, uint16: %u \r\n", plainStruct.m_int32, plainStruct.m_uint16);

    //PlainUnion un = {.bits = {1, 2, 3}};
    PlainUnion un = {.m_val = 0x123};
    printf("bit1: %d, bit2: %d, reserved: %d \r\n", un.bits.m_bit1, un.bits.m_bit2, un.bits.m_reserved);
}




