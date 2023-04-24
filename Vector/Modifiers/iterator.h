/*
 * @Author: chenlonglong 
 * @Date: 2023-04-14 11:19:46 
 * @Last Modified by: chenlonglong
 * @Last Modified time: 2023-04-16 19:29:58
 */
#ifndef MYTINYSTL_ITERATOR_H
#define MYTINYSTL_ITERATOR_H

#include <iterator>
#include <iostream>

namespace my_stl {
    template <class _Iterator>
    class reverse_iterator {
    protected:
        _Iterator current;
    public:
        typedef typename std::iterator_traits<_Iterator>::iterator_category iterator_category;
        typedef typename std::iterator_traits<_Iterator>::value_type value_type;
        typedef typename std::iterator_traits<_Iterator>::difference_type difference_type;
        typedef typename std::iterator_traits<_Iterator>::pointer pointer;
        typedef typename std::iterator_traits<_Iterator>::reference reference;

        typedef _Iterator iterator_type;
        typedef reverse_iterator<_Iterator> _Self;

        /* Constructs reverse_iterator object */
        reverse_iterator() {};
        explicit reverse_iterator(iterator_type it) : current(it) {}
        template <class Iter> reverse_iterator(const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {}

        /* Member functions */
        iterator_type base() const { return current; }
        reference operator*() const {
            _Iterator temp = current;
            return *--temp; 
        }
        _Self operator+(difference_type n) const {
            std::cout << "operator+ \n";
            return _Self(current - n);
        }
        _Self& operator++() {
            --current;
            return *this;
        }
        _Self operator++(int) {
            _Self temp = *this;
            --current;
            return temp;
        }
        _Self& operator+=(difference_type n) {
            current -= n;
            return *this;
        }
        _Self operator-(difference_type n) const {
            std::cout << "operator- \n";
            return _Self(current + n);
        }
        _Self& operator--() {
            ++current;
            return *this;
        }
        _Self operator--(int) {
            _Self temp = *this;
            ++current;
            return temp;
        }
        _Self& operator-=(difference_type n) {
            current += n;
            return *this;
        }
        pointer operator->() const { return &(operator*()); }
        reference operator[](difference_type n) const {
            return *(*this + n);
        }
    };
    /* Non-member function overloads */
    template <class Iterator>
    inline bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    inline bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(lhs == rhs);
    }

    template <class Iterator>
    inline bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() < lhs.base();
    }

    template <class Iterator>
    inline bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(rhs < lhs);
    }

    template <class Iterator>
    inline bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs < lhs;
    }

    template <class Iterator>
    inline bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(lhs < rhs);
    }

    template <class Iterator>
    inline reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
        std::cout << "free operator+ \n";
        return reverse_iterator<Iterator>(rev_it.base() - n);
    }

    template <class Iterator>
    inline typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        std::cout << "free operator- \n";
        return rhs.base() - lhs.base();
    }
}

#endif /* MYTINYSTL_ITERATOR_H */
