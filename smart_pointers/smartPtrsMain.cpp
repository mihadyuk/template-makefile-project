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
    printf("ptr refCnt: %d \r\n", ptr.refCnt());
    SmartPtr<uint32_t> ptr2(ptr);
    printf("ptr2 refCnt: %d \r\n", ptr2.refCnt());
    SmartPtr<uint32_t> ptr3(new uint32_t(11));
    printf("ptr3 refCnt: %d \r\n", ptr3.refCnt());
    ptr3 = ptr2;
    SmartPtr<uint32_t> ptr4;
    printf("ptr4 refCnt: %d \r\n", ptr4.refCnt());
    ptr4 = ptr2;
    printf("ptr4 refCnt: %d \r\n", ptr4.refCnt());
    printf("ptr3 refCnt: %d \r\n", ptr3.refCnt());
    printf("ptr refCnt: %d \r\n", ptr.refCnt());
}
