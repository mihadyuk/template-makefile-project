/*
 * templateExample.h
 *
 *  Created on: Sep 20, 2018
 *      Author: amihadyuk
 */

#ifndef TEMPLATES_TEMPLATEEXAMPLE_H_
#define TEMPLATES_TEMPLATEEXAMPLE_H_
#include <stddef.h>

template<typename T, size_t arraySize>
class Array {
public:
    Array() = default;

    size_t size() const { return arraySize; }

    T& value(size_t index) const {
        static_assert(index < arraySize, "index is out of range");
        return m_array[index];
    }

    const T& operator[](size_t index) const {
        static_assert(index < arraySize, "index is out of range");
        return m_array[index];
    }

    T& operator[](size_t index) {
        static_assert(index < arraySize, "index is out of range");
        return m_array[index];
    }
private:

    T m_array[arraySize];
};



#endif /* TEMPLATES_TEMPLATEEXAMPLE_H_ */
