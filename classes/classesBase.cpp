/*
 * classesBase.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: Andrey
 */

#include "classesBase.h"
#include <stdio.h>

Base::Base(const char *name) : m_name(name) {
    printf("Base \"%s\": ctor %p \r\n", m_name, (void *)this);
}

Base::Base(const Base &src) : m_name(src.m_name) {
    printf("Base: copy ctor \"%s\" %p = %p \r\n", m_name, (void *)this, (void *)&src);
}

Base::Base(Base &&src) : m_name(src.m_name) {
    printf("Base: move ctor \"%s\" %p = %p \r\n", m_name, (void *)this, (void *)&src);
}

Base::~Base() {
    printf("Base: dtor \"%s\" %p \r\n", m_name, (void *)this);
}

Base& Base::operator=(const Base &src) {
    if (this == &src)
        return *this;
    m_name = src.m_name;
    printf("Base: \"%s\" %p = %p \r\n", m_name, (void *)this, (void *)&src);
    return *this;
}

Base& Base::operator=(Base &&src) {
    if (this == &src)
        return *this;
    m_name = src.m_name;
    printf("Base: move \"%s\" %p = %p \r\n", m_name, (void *)this, (void *)&src);
    return *this;
}

