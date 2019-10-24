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
    SmartPtr() = default;
    SmartPtr(T *p);
    SmartPtr(const SmartPtr<T> &src) = delete;
    SmartPtr(SmartPtr<T> &&src)      = delete;
    SmartPtr<T>& operator=(const SmartPtr<T> &src) = delete;
    SmartPtr<T>& operator=(SmartPtr<T> &&src)      = delete;
    virtual ~SmartPtr();

private:
    T *m_p             = nullptr;
    uint32_t *m_refCnt = nullptr;
};

template <typename T>
SmartPtr<T>::SmartPtr(T *p) : m_p(p) {
    if (m_p) {
        assert(m_refCnt == nullptr);
        m_refCnt = new uint32_t(1);
        assert(*m_refCnt == 1);
    }
}

template <typename T>
SmartPtr<T>::~SmartPtr() {
    if (m_refCnt) {
        (*m_refCnt)--;
        if (*m_refCnt == 0 && m_p) {
            delete m_p;
            delete m_refCnt;
            m_p = nullptr;
            m_refCnt = nullptr;
        }
    }
}

}

#endif /* SMART_POINTERS_SMARTPTR_H_ */
