/*
 * templateUnit2.cpp
 *
 *  Created on: Sep 20, 2018
 *      Author: amihadyuk
 */
#include <stdint.h>
#include <stdio.h>
#include "templateUnit2.h"
#include "templateExample.h"

static Array<uint32_t, 10> g_array;

void templateUnit2() {

    for (size_t i = 0; i < g_array.size(); i++) {
        g_array[i] = (uint32_t)i;
        printf("unit2: %u \r\n", g_array.value(i));
    }
}




