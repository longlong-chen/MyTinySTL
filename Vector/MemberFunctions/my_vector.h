/*
 * @Author: chenlonglong 
 * @Date: 2023-04-08 11:55:20 
 * @Last Modified by:   chenlonglong 
 * @Last Modified time: 2023-04-08 11:55:20 
 */
#ifndef __MYTINYSTL_VECTOR_H
#define __MYTINYSTL_VECTOR_H

#include<memory> /* allocator */
#include<cstddef> /* ptrdiff_t / size_t */

namespace my_stl {
    template <class T, class Alloc = std::allocator<T>>
    class my_vector {
    public:
        typedef T           value_type;
        typedef value_type* pointer;
        typedef value_type* iterator;
        typedef value_type& reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
    protected:
        typedef std::allocator<T> data_allocator;
        iterator start;          // The head of the space currently used.
        iterator finish;         //The tail of the space currently used.
        iterator end_of_storage; // The tail of the currently available space.

    }
}

#endif // __MYTINYSTL_VECTOR_H