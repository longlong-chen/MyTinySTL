/*
 * @Author: chenlonglong 
 * @Date: 2023-04-08 11:55:20 
 * @Last Modified by: chenlonglong
 * @Last Modified time: 2023-04-11 18:06:17
 */
#ifndef __MYTINYSTL_VECTOR_H
#define __MYTINYSTL_VECTOR_H

#include<memory> /* allocator */
#include<cstddef> /* ptrdiff_t / size_t */
#include<initializer_list> /* std::initializer_list */
#include<iterator> /* std::distance() */
#include<iostream> /* std::out */

namespace my_stl {
    template <class T>
    class my_vector {
    public:
        typedef T           value_type;
        typedef value_type* pointer;
        typedef value_type* iterator;
        typedef value_type& reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;

        typedef std::allocator<T> data_allocator;
        typedef std::allocator<T> allocator_type;
    private:
        iterator start;          // The head of the space currently used.
        iterator finish;         //The tail of the space currently used.
        iterator end_of_storage; // The tail of the currently available space.
    public:
        explicit my_vector();
        explicit my_vector(size_type n);
        my_vector(size_type n, const value_type& val);
        // template <class InputIterator> my_vector(InputIterator first, InputIterator last);
        my_vector(const my_vector& x);
        /*  move constructor */
        my_vector(my_vector&& x) noexcept;
        /* initializer list constructor: constructs container with a copy of each of the elements in il, in the same order */
        my_vector(std::initializer_list<value_type> il);
    };

    /* Constructor function relize */
    template <class T>
    my_vector<T>::my_vector() : start(0), finish(0), end_of_storage(0) { std::cout << "empty container constructor\n"; }
    
    template <class T>
    my_vector<T>::my_vector(size_type n) {
        std::cout << "fill constructor\n";
        start = data_allocator().allocate(n);
        finish = start + n;
        end_of_storage = finish;
    }

    template <class T>
    my_vector<T>::my_vector(size_type n, const value_type& val) {
        std::cout << "fill constructor with val\n";
        start = data_allocator().allocate(n);
        finish = start + n;
        end_of_storage = finish;
        std::uninitialized_fill_n(start, n, val);
    }

    // template <class T>
    // template <class InputIterator>
    // my_vector<T>::my_vector(InputIterator first, InputIterator last) {
    //     const size_type n = std::distance(first, last);
    //     start = data_allocator().allocate(n);
    //     finish = start + n;
    //     end_of_storage = finish;
    //     std::uninitialized_copy(first, last, start);
    // }

    template <class T>
    my_vector<T>::my_vector(const my_vector& x) {
        std::cout << "copy Constructor\n";
        const size_type n = std::distance(x.start, x.finish);
        start = data_allocator().allocate(n);
        finish = start + n;
        end_of_storage = finish;
        std::uninitialized_copy(x.start, x.finish, start);
    }

    template <class T> 
    my_vector<T>::my_vector(my_vector&& x) noexcept : start(x.start), finish(x.finish), end_of_storage(x.end_of_storage) {
        std::cout << "move constructor\n";
        x.start = nullptr;
        x.finish = nullptr;
        x.end_of_storage = nullptr;
    }

    template <class T> 
    my_vector<T>::my_vector(std::initializer_list<value_type> il) {
        std::cout << "initializer list constructor\n";
        const size_type n = std::distance(il.begin(), il.end());
        start = data_allocator().allocate(n);
        finish = start + n;
        end_of_storage = finish;
        std::uninitialized_copy(il.begin(), il.end(), start);
    }
}

#endif // __MYTINYSTL_VECTOR_H

/* distance and allocator wait to deal with*/

/**
 * bug :error: no type named ‘difference_type’ in ‘struct std::iterator_traits<int>’
 * analyse: vector is not to my_vector
*/