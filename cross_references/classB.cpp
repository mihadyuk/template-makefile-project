/*
 * ClassA.cpp
 *
 *  Created on: 3 ���. 2019 �.
 *      Author: Andrey
 */

#include "classB.h"
#include "classA.h"

namespace cross_references {

void ClassB::print() {
        //m_ref.print();
        std::cout << "ClassB" << std::endl;
}

}


