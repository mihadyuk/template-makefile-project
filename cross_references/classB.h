/*
 * ClassA.h
 *
 *  Created on: 3 окт. 2019 г.
 *      Author: Andrey
 */

#ifndef CROSS_REFERENCES_CLASSB_H_
#define CROSS_REFERENCES_CLASSB_H_
#include <iostream>


namespace cross_references {

class ClassA;

class ClassB {
public:
    ClassB(ClassA& ref) : m_ref(ref){

    }
    virtual ~ClassB() {}

    void print();

    //void set(ClassA *ref) { m_ref = ref; }

private:
    ClassA &m_ref;
};

}

#endif /* CROSS_REFERENCES_CLASSA_H_ */
