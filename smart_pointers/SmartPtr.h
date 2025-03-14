/*
 * SmartPtr.h
 *
 *  Created on: Oct 24, 2019
 *      Author: amihadyuk
 */

#ifndef SMART_POINTERS_SMARTPTR_H_
#define SMART_POINTERS_SMARTPTR_H_
#include <assert.h>
#include <stdint.h>

namespace smart_pointers {

template <typename T>
class SmartPtr {
public:
    SmartPtr();
    SmartPtr(T *p);
    SmartPtr(const SmartPtr<T> &src);
    SmartPtr(SmartPtr<T> &&src)      = delete;
    SmartPtr<T>& operator=(const SmartPtr<T> &src);
    SmartPtr<T>& operator=(SmartPtr<T> &&src)      = delete;
    T& operator*() const {
     return *m_p;
    }

    T* operator->() const {
      return m_p;
    }
    virtual ~SmartPtr();

    uint32_t refCnt() const;
private:
    void decrementRefCnt();

    T *m_p;
    uint32_t *m_refCnt;
};

template <typename T>
SmartPtr<T>::SmartPtr() : m_p(nullptr), m_refCnt(nullptr) {}

template <typename T>
SmartPtr<T>::SmartPtr(T *p) : m_p(p), m_refCnt(nullptr) {

    if (m_p) {
        m_refCnt = new uint32_t(1);
        assert(*m_refCnt == 1);
    }
}

template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T> &src) {
    if (this == &src)
        return *this;

    decrementRefCnt();

    m_refCnt = src.m_refCnt;
    m_p      = src.m_p;
    if (m_refCnt)
        *m_refCnt += 1;
    return *this;
}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T> &src) : m_p(src.m_p), m_refCnt(src.m_refCnt) {
    if (m_refCnt)
        *m_refCnt += 1;
}

template <typename T>
SmartPtr<T>::~SmartPtr() {
    decrementRefCnt();
}

template <typename T>
void SmartPtr<T>::decrementRefCnt() {
    if (m_refCnt) {
        assert(m_p);
        assert(*m_refCnt > 0);
        (*m_refCnt)--;
        if (*m_refCnt == 0 && m_p) {

            delete m_refCnt;
            m_refCnt = nullptr;

            delete m_p;
            m_p = nullptr;
        }
    }
}

template <typename T>
uint32_t SmartPtr<T>::refCnt() const {
    uint32_t retval = 0;
    if (m_refCnt)
        retval = *m_refCnt;
    return retval;
}

}

#endif /* SMART_POINTERS_SMARTPTR_H_ */
