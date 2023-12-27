/*
 * templateUnit1.cpp
 *
 *  Created on: Sep 20, 2018
 *      Author: amihadyuk
 */
#include <stdint.h>
#include <stdio.h>
#include "templateUnit1.h"
#include "templateExample.h"
#include "templateCallback.h"



//static Array<uint32_t, 10> g_array;

static void func1(int value) {
    printf("func1 value: %d\n", value);
}

static void func2(int value) {
    printf("func2 value: %d\n", value);
}

void templateUnit1() {

    Callback<std::function<void(int)>, int> callbacks;
    std::function<void(int)> fn1(func1);
    std::function<void(int)> fn2(std::bind(&func1, std::placeholders::_1));
    //auto ptr1 = fn1.target<void(*)(int)>();
    //auto ptr2 = fn2.target<std::function<void(int)>>();
    callbacks.add(func1);
    callbacks.add(func1);
    callbacks.remove(func1);
    callbacks.add(func1);
    callbacks.add(func2);
    callbacks.remove(func2);

    callbacks.call(10);
#if 0
    for (size_t i = 0; i < g_array.size(); i++) {
        g_array[i] = (uint32_t)i;
        printf("unit1: %u \r\n", g_array.value(i));
    }
#endif
}




