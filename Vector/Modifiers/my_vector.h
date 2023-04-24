/*
 * @Author: chenlonglong 
 * @Date: 2023-04-08 11:55:20 
 * @Last Modified by: chenlonglong
 * @Last Modified time: 2023-04-23 09:51:00
 */
#ifndef __MYTINYSTL_VECTOR_H
#define __MYTINYSTL_VECTOR_H

#include<memory> /* allocator */
#include<cstddef> /* ptrdiff_t / size_t */
#include<initializer_list> /* std::initializer_list */
#include<iterator> /* std::distance() */
#include<iostream> /* std::out */
#include<algorithm> /* copy / move */
#include<cassert> /* assert */
#include "iterator.h"

namespace my_stl {
    template <class T>
    class my_vector {
    public:
        typedef T           value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type* iterator;
        typedef const value_type* const_iterator;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;

        typedef my_stl::reverse_iterator<iterator> reverse_iterator;
        typedef my_stl::reverse_iterator<const_iterator> const_reverse_iterator;

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


        /* destructor */
        ~my_vector();


        /* operator= */
        /* copy assignment */
        my_vector& operator= (const my_vector& x);
        /* move assignment */
        my_vector& operator= (my_vector&& x) noexcept;
        /* initializer list assignment */
        my_vector& operator= (std::initializer_list<value_type> il);


        /* Iterators */
        iterator begin() noexcept { return start; }
        const_iterator begin() const noexcept { return start; }
        iterator end() noexcept { return finish; }
        const_iterator end() const noexcept { return finish; }
        const_iterator cbegin() const noexcept { begin(); }
        const_iterator cend() const noexcept { end(); };

        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const noexcept { const_reverse_iterator(end()); }
        reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
        const_reverse_iterator crbegin() const noexcept { return rbegin(); }
        const_reverse_iterator crend() const noexcept { return rend(); }
        
        /* Element access */
        reference operator[](size_type n) { return *(begin() + n); }
        const_reference operator[](size_type n) const { return *(begin() + n); }
        reference at(size_type n) { if(n >= size()) throw std::out_of_range("vector<T>::at() subscript out of range"); return (*this)[n]; }
        const_reference at(size_type n) const { if(n >= size()) throw std::out_of_range("vector<T>::at() subscript out of range"); return (*this)[n]; } 
        reference front() { return *begin(); }
        const_reference front() const { return *begin(); }
        reference back() { return *(end() - 1); }
        const_reference back() const { return *(end() - 1); }
        value_type* data() noexcept { return start; }
        const value_type* data() const noexcept { return start; }

        /* Capacity */
        size_type size() const noexcept { return size_type(end() - begin()); }
        size_type max_size() const noexcept { return size_type(-1) / sizeof(T); }
        bool empty() const noexcept { return begin() == end(); }
        size_type capacity() const noexcept { return size_type(end_of_storage - begin()); }
        void resize(size_type n);
        void resize(size_type n, const value_type& val);
        void reserve(size_type n);
        void shrink_to_fit();

        /* Modifiers */
        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);
        template <class InputIterator> void assign(InputIterator first, InputIterator last);
        void assign(size_type n, const value_type& val);
        void assign(std::initializer_list<value_type> il);
        void swap(my_vector& x);
        void pop_back() { --finish; data_allocator().destroy(finish); }
        void clear() noexcept { erase(begin(), end()); }

        /* others */
        void fill_assign(size_type n, const value_type& val);
    };

    /* others */
    template <class T>
    void my_vector<T>::fill_assign(size_type n, const value_type& val) {
        if(n > capacity()) {
            my_vector<T> tmp(n, val);
            tmp.swap(*this);
        }
        else if(n > size()) {
            std::fill(begin(), end(), val);
            finish = std::uninitialized_fill_n(finish, n - size(), val);
        }
        else {
            erase(std::fill_n(begin(), n, val), end());
        }
    }

    /* Modifiers */
    template <class T>
    void my_vector<T>::swap(my_vector& x) {
        std::swap(start, x.start);
        std::swap(finish, x.finish);
        std::swap(end_of_storage, x.end_of_storage);
    }

    template <class T>
    my_vector<T>::iterator my_vector<T>::erase(const_iterator position) {
        assert(position >= begin() && position < end());
        iterator xpos = start + (position - begin());
        std::move(xpos + 1, finish, xpos);
        --finish;
        data_allocator().destroy(finish);
        return xpos;
    }

    template <class T>
    my_vector<T>::iterator my_vector<T>::erase(const_iterator first, const_iterator last) {
        assert(first >= begin() && last <= end() && first <= last);
        const size_type n = first - begin();
        iterator xpos = start + (first - begin());
        iterator tmp = std::move(xpos + (last - first), finish, xpos);
        for(; tmp != finish; ++tmp) {
            data_allocator().destroy(tmp);
        }
        finish = finish - (last - first);
        return start + n;
    }

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

    /* destructor */
    template <class T> 
    my_vector<T>::~my_vector() {
        iterator tmp = start;
        // size_type n = 0;
        for(; tmp < finish; ++tmp) {
            data_allocator().destroy(tmp);
            // ++n;
        }
        data_allocator().deallocate(start, end_of_storage - start);
        start = finish = end_of_storage = nullptr;
    }

    template <class T>
    my_vector<T>& my_vector<T>::operator=(const my_vector& x) {
        if(&x != this) {
            const size_type n = x.finish - x.start;
            if(n > end_of_storage - start) {
                iterator tmp = data_allocator().allocate(n);
                std::uninitialized_copy(x.start, x.finish, tmp);
                iterator pIndex = start;
                for(; pIndex < finish; ++pIndex) {
                    data_allocator().destroy(pIndex);
                }
                data_allocator().deallocate(start, end_of_storage - start);
                start = tmp;
                end_of_storage = start + n;
            }
            else if(finish - start >= n) {
                iterator index = std::copy(x.start, x.finish, start);
                iterator pIndex = start;
                for(; pIndex < finish; ++pIndex) {
                    data_allocator().destroy(pIndex);
                }
            }
            else {
                size_type size = finish - start;
                std::copy(x.start, x.start + size, start);
                std::uninitialized_copy(x.start + size, x.finish, finish);
            }
            finish = start + n;
        }
        return *this;
    }

    template <class T>
    my_vector<T>& my_vector<T>::operator=(my_vector&& x) noexcept {
        iterator pIndex = start;
        for(; pIndex < finish; ++pIndex) {
            data_allocator().destroy(pIndex);
        }
        data_allocator().deallocate(start, end_of_storage - start);
        start = x.start;
        finish = x.finish;
        end_of_storage = x.end_of_storage;
        x.start = x.finish = x.end_of_storage = nullptr;
        return *this;
    }

    template <class T>
    my_vector<T>& my_vector<T>::operator=(std::initializer_list<value_type> il) {
        my_vector<T> x(il);
        if(&x != this) {
            const size_type n = x.finish - x.start;
            if(n > end_of_storage - start) {
                iterator tmp = data_allocator().allocate(n);
                std::uninitialized_copy(x.start, x.finish, tmp);
                iterator pIndex = start;
                for(; pIndex < finish; ++pIndex) {
                    data_allocator().destroy(pIndex);
                }
                data_allocator().deallocate(start, end_of_storage - start);
                start = tmp;
                end_of_storage = start + n;
            }
            else if(finish - start >= n) {
                iterator index = std::copy(x.start, x.finish, start);
                iterator pIndex = start;
                for(; pIndex < finish; ++pIndex) {
                    data_allocator().destroy(pIndex);
                }
            }
            else {
                size_type size = finish - start;
                std::copy(x.start, x.start + size, start);
                std::uninitialized_copy(x.start + size, x.finish, finish);
            }
            finish = start + n;
        }
        return *this;
    }

}

#endif // __MYTINYSTL_VECTOR_H

/* distance and allocator wait to deal with*/

/**
 * bug :error: no type named ‘difference_type’ in ‘struct std::iterator_traits<int>’
 * analyse: vector is not to my_vector
*/