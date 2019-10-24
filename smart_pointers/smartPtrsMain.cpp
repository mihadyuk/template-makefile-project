/*
 * smartPtrsMain.cpp
 *
 *  Created on: Oct 24, 2019
 *      Author: amihadyuk
 */

#include "smartPtrsMain.h"
#include "SmartPtr.h"

using namespace smart_pointers;

void smartPtrsMain() {

    SmartPtr<uint32_t> ptr(new uint32_t(10));
}
