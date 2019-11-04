/*
 * VirtualInheritanceMain.cpp
 *
 *  Created on: 4 но€б. 2019 г.
 *      Author: Andrey
 */
#include <stdint.h>
#include <stdio.h>
#include "VirtualInheritanceMain.h"

class BaseValue {
public:
    virtual void value() const { printf("BaseValue\r\n"); }
private:
};

class ValueL : public virtual BaseValue {
public:
    virtual void valueL() const { printf("ValueL\r\n"); }
    //virtual void value() const { printf("BaseValue overridden in L\r\n"); }
private:
};

class ValueR : public virtual BaseValue {
public:
    virtual void valueR() const { printf("ValueR\r\n"); }
    //virtual void value() const { printf("BaseValue overridden in R\r\n"); }
private:
};

class CombinedValue : public ValueR, ValueL {
public:
    virtual void valueCombined() const { printf("CombinedValue\r\n"); }
    //virtual void value() const { printf("BaseValue overridden in combined\r\n"); }
private:
};



void virtualInheritanceMain() {

    CombinedValue().value();
}
