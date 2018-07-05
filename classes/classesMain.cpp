/*
 * classesMain.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: Andrey
 */
#include "classesMain.h"
#include "classesBase.h"
#include <stdio.h>

struct Test {
    int32_t m_int32;
    uint32_t m_uint32;
    int16_t m_int16;

    Test() = default;
#if 0
    Test(volatile const Test &src) {
        m_int32  = src.m_int32;
        m_uint32 = src.m_uint32;
        m_int16  = src.m_int16;
    }

    Test& operator=(volatile const Test& src) {
        if (this == &src)
            return *this;
        m_int32  = src.m_int32;
        m_uint32 = src.m_uint32;
        m_int16  = src.m_int16;
        return *this;
    }
#endif
};

volatile Test va;
//Test va;

void classesMain() {

    Base a;
    Base b;
    Base c = a;
    Base d(b);

    b = a;
    Test test;
    test = const_cast<Test&>(va);
}



