/*
 * crossRefMain.cpp
 *
 *  Created on: 3 ���. 2019 �.
 *      Author: Andrey
 */

#include "crossRefMain.h"

#include "classA.h"
#include "classB.h"

using namespace cross_references;

#if 1
template<class A, class B>
class Bind {
public:
    Bind() : m_classA(m_classB), m_classB(m_classA) {
    }
    A m_classA;
    B m_classB;
};
#endif

//ClassA classA;
//ClassB classB;

Bind<ClassA, ClassB> bind;

void crossRefMain() {
    //classA.set(&classB);
    //classB.set(&classA);
    //classA.print();
    //classB.print();
    bind.m_classA.print();
    bind.m_classB.print();
}
