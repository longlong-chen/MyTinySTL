/*
 * @Author: chenlonglong 
 * @Date: 2023-04-08 11:55:20 
 * @Last Modified by: chenlonglong
 * @Last Modified time: 2023-05-04 11:40:22
 */
#ifndef __MYTINYSTL_VECTOR_H
#define __MYTINYSTL_VECTOR_H

#include<memory> /* allocator */
#include<cstddef> /* ptrdiff_t / size_t */
#include<initializer_list> /* std::initializer_list */
#include<iterator> /* std::distance() */
#include<iostream> /* std::out */
#include<algorithm> /* copy / move  / copy_backward */
#include<cassert> /* assert */
#include "iterator.h"
#include "type_traits.h"
#include "construct_destroy.h"
#include "mystl_config.h"

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
        template <class InputIterator> my_vector(InputIterator first, InputIterator last);
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
        reference at(size_type n) { if(n >= size()) throw std::out_of_range("my_vector<T>::at() subscript out of range"); return (*this)[n]; }
        const_reference at(size_type n) const { if(n >= size()) throw std::out_of_range("my_vector<T>::at() subscript out of range"); return (*this)[n]; } 
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
        template <class InputIterator> void assign(InputIterator first, InputIterator last) {
            typedef typename _Is_integer<InputIterator>::_Integral _Integral;

        }
        void assign(size_type n, const value_type& val) { fill_assign(n, val); }
        void assign(std::initializer_list<value_type> il);
        void swap(my_vector& x);
        void pop_back() { --finish; destroy(finish); }
        void clear() noexcept { erase(begin(), end()); }
        void push_back(const value_type& val);
        void push_back();
        void push_back(value_type&& val);
        template <class... Args> void emplace(const_iterator position, Args&&... args);
        iterator insert(const_iterator position, const value_type& val);
        iterator insert(const_iterator position);
        iterator insert(const_iterator position, size_type n, const value_type& val);
        template <class InputIterator> iterator insert(const_iterator position, InputIterator first, InputIterator last);
        iterator insert(const_iterator position, value_type&& val);
        iterator insert(const_iterator position, std::initializer_list<value_type> il);

        /* others */
        void fill_assign(size_type n, const value_type& val);
        template <Integer> void assign_dispatch(Integer n, Integer val, __true_type) { fill_assign((size_type) n, val); }
        template <class InputIterator> void assign_dispatch(InputIterator first, InputIterator last, __false_type) { assign_aux(first, last, __ITERATOR_CATEGORY(first)); }
        template <class InputIterator> void assign_aux(InputIterator first, InputIterator last, input_iterator_tag);
        template <class ForwardIterator> void assign_aux(ForwardIterator first, ForwardIterator last, forward_iterator_tag);
        template <class Integer> void initialize_aux(Integer n, Integer value, __true_type);
        template <class InputIterator> void initialize_aux(InputIterator first, InputIterator last, __false_type);
        void fill_insert(iterator position, size_type n, const value_type& val);


    protected:
        template <class InputIterator> void range_initialize(InputIterator first, InputIterator last, input_iterator_tag);
        template <class ForwardIterator> void range_initialize(ForwardIterator first, ForwardIterator last, forward_iterator_tag);
        template <class ForwardIterator> iterator allocate_and_copy(size_type n , ForwardIterator first, ForwardIterator last) {
            iterator result = data_allocator().allocate(n);
            std::uninitialized_copy(first, last, result);
            return result;
        }
        void insert_aux(iterator position, const value_type& val);
        void insert_aux(iterator position);
        // This function is only called by the constructor.
        template <class ForwardIterator> void range_insert(iterator position, ForwardIterator first, ForwardIterator last, forward_iterator_tag);
        template <class InputIterator> void range_insert(iterator position, InputIterator first, InputIterator last, input_iterator_tag);
    };

    /* others */
    template <class T>
    void my_vector<T>::fill_insert(iterator position, size_type n, const value_type& val) {
        if(n != 0) {
            if(size_type(end_of_storage - finish) >= n) {
                value_type val_copy = val;
                const size_type elems_after = finish - position;
                iterator old_finish = finish;
                if(elems_after > n) {
                    std::uninitialized_copy(finish - n, finish, finish);
                    finish += n;
                    std::copy_backward(position, old_finish - n, old_finish);
                    std::fill(position, position + n, val_copy);
                }
                else {
                    std::uninitialized_fill_n(finish, n - elems_after, val_copy);
                    finish += n - elems_after;
                    std::uninitialized_copy(position, old_finish, finish);
                    finish += elems_after;
                    std::fill(position, old_finish, val_copy);
                }
            }
            else {
                const size_type old_size = size();
                const size_type len = old_size + max(old_size, n);
                iterator new_start = data_allocator().allocate(len);
                iterator new_finish = new_start;
                MYSTL_TRY {
                    new_finish = std::uninitialized_copy(start, position, new_start);
                    new_finish = std::uninitialized_fill_n(new_finish, n, val);
                    new_finish = std::uninitialized_copy(position, finish, new_finish);
                }
                MYSTL_UNWIND((destroy(new_start,new_finish),data_allocator().deallocate(new_start,len)));
                destroy(start, finish);
                data_allocator().deallocate(start, end_of_storage - start);
                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + len;
            }
        }
    } 

    template <class T> template <class ForwardIterator> 
    void my_vector<T>::range_insert(iterator position, ForwardIterator first, ForwardIterator last, forward_iterator_tag) {
        if(first != last) {
            const size_type n = distance(first, last);
            if(size_type(end_of_storage - finish) >= n) {
                const size_type elems_after = finish - position;
                iterator old_finish = finish;
                if(elems_after > n) {
                    std::uninitialized_copy(finish - n, finish, finish);
                    finish += n;
                    std::copy_backward(position, old_finish - n, old_finish);
                    std::copy(first, last, position);
                }
                else {
                    ForwardIterator mid = first;
                    advance(mid, elems_after);
                    std::uninitialized_copy(mid, last, finish);
                    finish += n - elems_after;
                    std::uninitialized_copy(position, old_finish, finish);
                    finish += elems_after;
                    std::copy(first, mid, position);
                }
            }
            else {
                const size_type old_size = size();
                const size_type len = old_size + max(old_size, n);
                iterator new_start = data_allocator().allocate(len);
                iterator new_finish = new_start;
                MYSTL_TRY {
                    new_finish = std::uninitialized_copy(start, position, new_start);
                    new_finish = std::uninitialized_copy(first, last, new_finish);
                    new_finish = std::uninitialized_copy(position, finish, new_finish);
                }
                MYSTL_UNWIND((destroy(new_start,new_finish),data_allocator().deallocate(new_start,len)));
                destroy(start, finish);
                data_allocator().deallocate(start, end_of_storage - start);
                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + len;
            }
        }
    }

    template<class T> template <class InputIterator> 
    void my_vector<T>::range_insert(iterator position, InputIterator first, InputIterator last, input_iterator_tag) {
        for(; first != last; ++first) {
            position = insert(position, *first);
            ++position;
        }
    }

    template <class T> template <class Integer> 
    void my_vector<T>::initialize_aux(Integer n, Integer value, __true_type) {
        start = data_allocator().allocate(n);
        end_of_storage = start + n;
        finish = std::uninitialized_fill_n(start, n, value);
    }

    template <class T> template <class InputIterator>
    void my_vector<T>::initialize_aux(InputIterator first, InputIterator last, __false_type) {
        range_initialize(first, last, __ITERATOR_CATEGORY(first));
    }

    template <class T>
    void my_vector<T>::insert_aux(iterator position, const value_type& val) {
        if(finish != end_of_storage) {
            construct(finish, *(finish - 1));
            ++finish;
            value_type val_copy = val;
            std::copy_backward(position, finish - 2, finish - 1);
            *position = val_copy;
        }
        else {
            const size_type old_size = size();
            const size_type len = old_size != 0 ? 2 * old_size : 1;
            iterator new_start = data_allocator().allocate(len);
            iterator new_finish = new_start;
            MYSTL_TRY {
                new_finish = std::uninitialized_copy(start, position, new_start);
                construct(new_finish, val);
                ++new_finish;
                new_finish = std::uninitialized_copy(position, finish, new_finish);
            }
            MYSTL_UNWIND((destroy(new_start, new_finish),data_allocator().deallocate(new_start,len)));
            destroy(begin(), end());
            data_allocator().deallocate(start, end_of_storage - start);
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;
        }
    }

    template <class T>
    void my_vector<T>::insert_aux(iterator position) {
        if(finish != end_of_storage) {
            construct(finish, *(finish - 1));
            ++finish;
            std::copy_backward(position, finish - 2, finish - 1);
            *position = T();
        }
        else {
            const size_type old_size = size();
            const size_type len = old_size != 0 ? 2 * old_size : 1;
            iterator new_start = data_allocator().allocate(len);
            iterator new_finish = new_start;
            MYSTL_TRY {
                new_finish = std::uninitialized_copy(start, position, new_start);
                construct(new_finish);
                ++new_finish;
                new_finish = std::uninitialized_copy(position, finish, new_finish);
            }
            MYSTL_UNWIND((destroy(new_start,new_finish),data_allocator().deallocate(new_start,len)));
            destroy(begin(), end());
            data_allocator().deallocate(start, end_of_storage - start);
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;    
        }
    }

    template<class T> template <class InputIterator>
    void my_vector<T>::range_initialize(InputIterator first, InputIterator last, input_iterator_tag) {
        for(; first != last; ++first) push_back(*first);
    }

    template<class T> template <class ForwardIterator>
    void my_vector<T>::range_initialize(ForwardIterator first, ForwardIterator last, forward_iterator_tag) {
        const size_type n = distance(first, last);
        start = data_allocator().allocate(n);
        end_of_storage = start + n;
        finish = std::uninitialized_copy(first, last, start);
    }

    template <class T> template <class InputIterator>
    void my_vector<T>::assign_aux(InputIterator first, InputIterator last, input_iterator_tag) {
        iterator cur = begin();
        for(; first != last && cur != end(); ++cur, ++first) *cur = *first;
        if(first == last) erase(cur, end());
        else insert(end(), first, last);
    }

    template <class T> template <class ForwardIterator> 
    void my_vector<T>::assign_aux(ForwardIterator first, ForwardIterator last, forward_iterator_tag) {
        const size_type len = distance(first, last);

        if(len > capacity()) {
            iterator tmp = allocate_and_copy(len, first, last);
            destroy(start, finish);
            data_allocator().deallocate(start, end_of_storage - start);
            start = tmp;
            end_of_storage = finish = start + len;
        }
        else if(size() >= len) {
            iterator new_finish = std::copy(first, last, start);
            destroy(new_finish, finish);
            finish = new_finish;
        }
        else {
            ForwardIterator mid = first;
            advance(mid, size());
            std::copy(first, mid, start);
            finish = std::uninitialized_copy(mid, last, finish);
        }
    }

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
    typename my_vector<T>::iterator my_vector<T>::insert(const_iterator position, const value_type& val) {
        size_type n = position - begin();
        if(finish != end_of_storage && position == end()) {
            construct(finish, val);
            ++finish;
        }
        else {
            insert_aux(position, val);
        }
        return begin() + n;
    }

    template <class T>
    typename my_vector<T>::iterator my_vector<T>::insert(const_iterator position) {
        size_type n = position - begin();
        if(finish != end_of_storage && position == end()) {
            construct(finish);
            ++finish;
        }
        else {
            insert_aux(position);
        }
        return begin() + n;
    }

    template <class T>
    void my_vector<T>::push_back(const value_type& val) {
        if(finish != end_of_storage) {
            construct(finish, val);
            ++finish;
        }
        else {
            insert_aux(end(), val);
        }
    }

    template <class T>
    void my_vector<T>::push_back() {
        if(finish != end_of_storage) {
            construct(finish);
            ++finish;
        }
        else {
            insert_aux(end());
        }
    }

    template <class T> 
    void my_vector<T>::push_back(value_type&& val) {
        // wait emplace
    }

    template <class T>
    void my_vector<T>::swap(my_vector& x) {
        std::swap(start, x.start);
        std::swap(finish, x.finish);
        std::swap(end_of_storage, x.end_of_storage);
    }

    template <class T>
    typename my_vector<T>::iterator my_vector<T>::erase(const_iterator position) {
        assert(position >= begin() && position < end());
        iterator xpos = start + (position - begin());
        std::move(xpos + 1, finish, xpos);
        --finish;
        data_allocator().destroy(finish);
        return xpos;
    }

    template <class T>
    typename my_vector<T>::iterator my_vector<T>::erase(const_iterator first, const_iterator last) {
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

    template <class T> template <class InputIterator>
    my_vector<T>::my_vector(InputIterator first, InputIterator last) {
        typedef typename _Is_integer<InputIterator>::_Integral _Integral;
        initialize_aux(first, last, _Integral());
    }

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