/*
 * memallocMain.cpp
 *
 *  Created on: 27 ���. 2018 �.
 *      Author: Andrey
 */
#include <new>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "memallocMain.h"


class Test {
    int32_t m_val = 0;
public:
    Test(int32_t val) : m_val(val) {
        std::cout << "Test: ctor " << m_val << std::endl;
    }
    Test(const Test &src) {
        std::cout << "Test: copy ctor " << m_val << std::endl;
    }
    Test(const Test &&src) {
            std::cout << "Test: move ctor " << m_val << std::endl;
    }
    ~Test() {
        std::cout << "Test: dtor " << std::endl;
    }
    Test& operator=(const Test& src) {
        if (this == &src)
            return *this;
        std::cout << "Test: operator= " << std::endl;
        return *this;
    }
};


void memallocMain() {
    //Test *buffer = (Test *)malloc(sizeof(Test));
    uint8_t *buffer = (uint8_t *)malloc(sizeof(Test));

    //*buffer = Test(10);
    //*(Test *)buffer = Test(10);
    Test *ptr = new (buffer) Test(10);
    assert((uint8_t *)ptr == buffer);
    //((Test *)buffer)->~Test();
    ptr->~Test();

    free(buffer);
}



