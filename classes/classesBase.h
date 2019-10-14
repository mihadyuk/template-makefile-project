/*
 * classesBase.h
 *
 *  Created on: Jul 5, 2018
 *      Author: Andrey
 */

#ifndef CLASSES_CLASSESBASE_H_
#define CLASSES_CLASSESBASE_H_
#include <stdio.h>

class Base {
public:
    Base() = delete;
    Base(const char *name);
    Base(const Base &src);
    Base(Base &&src);
    virtual ~Base();
    Base& operator=(const Base &src);
    Base& operator=(Base &&src);
private:
    const char *m_name = nullptr;
};

#endif /* CLASSES_CLASSESBASE_H_ */
