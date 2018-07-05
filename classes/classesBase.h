/*
 * classesBase.h
 *
 *  Created on: Jul 5, 2018
 *      Author: mihadyuk
 */

#ifndef CLASSES_CLASSESBASE_H_
#define CLASSES_CLASSESBASE_H_
#include <stdio.h>

class Base {
public:
    Base();
    Base(const Base &src);
    Base(const Base &&src);
    virtual ~Base();
    Base& operator=(const Base &src);
    Base& operator=(const Base &&src);
};

#endif /* CLASSES_CLASSESBASE_H_ */
