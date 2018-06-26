/*
 * exampleExceptions.cpp
 *
 *  Created on: 26 θών. 2018 γ.
 *      Author: Andrey
 */
#include <stdint.h>
#include <stdio.h>
#include <exception>
#include <stdexcept>
#include "exceptionsMain.h"
#include "exceptionsBase.h"


using namespace exceptionExamples;


void exceptionsMain() {
    printf ("exceptions example \r\n");
    try {
        throw std::invalid_argument("wrong arg");
    }
    catch (const std::exception &e) {
        printf("exception: %s \r\n", e.what());
    }
    catch (...) {
        printf("unknown exception \r\n");
    }
    printf("exit \r\n");
}




