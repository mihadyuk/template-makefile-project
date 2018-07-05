/*
 * classesBase.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: amihadyuk
 */

#include "classesBase.h"
#include <stdio.h>

Base::Base() {
    printf("Base: ctor %p \r\n", this);
}

Base::Base(const Base &src) {
    printf("Base: copy ctor %p \r\n", this);
}

Base::Base(const Base &&src) {
    printf("Base: move ctor %p \r\n", this);
}

Base::~Base() {
    printf("Base: dtor %p \r\n", this);
}

Base& Base::operator=(const Base &src) {
    printf("Base: %p = %p \r\n", &src, this);
    return *this;
}

Base& Base::operator=(const Base &&src) {
    printf("Base: move %p = %p \r\n", &src, this);
    return *this;
}

