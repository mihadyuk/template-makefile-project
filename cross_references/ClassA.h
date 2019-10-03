/*
 * ClassA.h
 *
 *  Created on: 3 окт. 2019 г.
 *      Author: Andrey
 */

#ifndef CROSS_REFERENCES_CLASSA_H_
#define CROSS_REFERENCES_CLASSA_H_
#include <iostream>
#include "IClassA.h"
#include "IClassB.h"

namespace cross_references {

class ClassB;

class ClassA {
public:
    ClassA(ClassB &ref) : m_ref(ref) {

    }
    virtual ~ClassA() {}

    void print();
    //void set(ClassB *ref) { m_ref = ref; }

private:
    ClassB &m_ref;
};

}

#endif /* CROSS_REFERENCES_CLASSA_H_ */
