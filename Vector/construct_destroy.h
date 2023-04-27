/*
 * @Author: chenlonglong 
 * @Date: 2023-04-27 10:22:05 
 * @Last Modified by: chenlonglong
 * @Last Modified time: 2023-04-27 10:52:07
 */
#ifndef __MYTINYSTL_CONSTRUCT_H
#define __MYTINYSTL_CONSTRUCT_H

#include <new>
#include "type_traits.h"

template <class T1, class T2>
inline void _Construct(T1* p, const T2& value) {
    new ((void*) p) T1(value);
}

template <class T1>
inline void _Construct(T1* p) {
    new ((void*) p) T1();
}

template <class T> 
inline void _Destroy(T* pointer) {
    pointer->~T();
}

template <class ForwardIterator>
void __destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
    for(; first != last; ++first) {
        destroy(&*first);
    }
}

template <class ForwardIterator>
void __destroy_aux(ForwardIterator, ForwardIterator, __true_type) {}

template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
    typedef typename __type_traits<T>::has_trivial_destructor Trivial_destructor;
    __destroy_aux(first, last, Trivial_destructor());
}

template <class ForwardIterator>
inline void _Destroy(ForwardIterator first, ForwardIterator last) {
    __destroy(first, last, __VALUE_TYPE(first));
}

inline void _Destroy(char*, char*) {}
inline void _Destroy(int*, int*) {}
inline void _Destroy(long*, long*) {}
inline void _Destroy(float*, float*) {}
inline void _Destroy(double*, double*) {}
inline void _Destroy(wchar_t*, wchar_t*) {}

template <class T1, class T2>
inline void construct(T1* p, const T2& value) {
    _Construct(p, value);
}

template <class T1>
inline void construct(T1* p) {
    _Construct(p);
}

template <class T>
inline void destroy(T* pointer) {
    _Destroy(pointer);
}

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
    _Destroy(first, last);
}

#endif /* __MYTINYSTL_CONSTRUCT_H */