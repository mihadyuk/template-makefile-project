/*
 * IClassA.h
 *
 *  Created on: 3 окт. 2019 г.
 *      Author: Andrey
 */

#ifndef CROSS_REFERENCES_ICLASSB_H_
#define CROSS_REFERENCES_ICLASSB_H_

namespace cross_references {

class IClassB {
public:
    virtual ~IClassB() {}

    virtual void print() = 0;
};

}

#endif /* CROSS_REFERENCES_ICLASSA_H_ */
