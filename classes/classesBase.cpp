/*
 * classesBase.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: Andrey
 */

#include "classesBase.h"
#include <stdio.h>

Base::Base() {
    printf("Base: ctor %p \r\n", (void *)this);
}

Base::Base(const Base &src) {
    printf("Base: copy ctor %p = %p \r\n", (void *)this, (void *)&src);
}

Base::Base(const Base &&src) {
    printf("Base: move ctor %p = %p \r\n", (void *)this, (void *)&src);
}

Base::~Base() {
    printf("Base: dtor %p \r\n", (void *)this);
}

Base& Base::operator=(const Base &src) {
    printf("Base: %p = %p \r\n", (void *)this, (void *)&src);
    return *this;
}

Base& Base::operator=(const Base &&src) {
    printf("Base: move %p = %p \r\n", (void *)this, (void *)&src);
    return *this;
}

