/*
 * ClassA.cpp
 *
 *  Created on: 3 окт. 2019 г.
 *      Author: Andrey
 */

#include "classA.h"
#include "classB.h"

namespace cross_references {

void ClassA::print() {
    //m_ref.print();
    std::cout << "ClassA" << std::endl;
}

}


