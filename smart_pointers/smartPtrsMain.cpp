/*
 * smartPtrsMain.cpp
 *
 *  Created on: Oct 24, 2019
 *      Author: amihadyuk
 */
#include <stdio.h>

#include "smartPtrsMain.h"
#include "SmartPtr.h"

using namespace smart_pointers;

void smartPtrsMain() {

    SmartPtr<uint32_t> ptr(new uint32_t(10));
    //SmartPtr<uint32_t> ptr;
    printf("refCnt: %d \r\n", ptr.refCnt());
    SmartPtr<uint32_t> ptr2(ptr);
    SmartPtr<uint32_t> ptr3;
    //ptr3 = ptr2;
    printf("refCnt: %d \r\n", ptr.refCnt());
}
