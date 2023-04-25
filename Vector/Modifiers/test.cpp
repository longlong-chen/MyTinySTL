#include "type_traits.h"
#include <iostream>
#include "iterator.h"
#include "my_vector.h"

void fun(__true_type) {
    std::cout << "Is Integer\n";
}

void fun(__false_type) {
    std::cout << "Is not Integer\n";
}

void fun1(random_access_iterator_tag) {
    std::cout << "Is random_access_iterator_tag\n";
}

void fun1(output_iterator_tag) {
    std::cout << "Is output_iterator_tag\n";
}

int main() {
    typedef typename _Is_integer<int>::_Integral _Integral;
    fun(_Integral());
    typedef typename _Is_integer<double>::_Integral _Integral2;
    fun(_Integral2());
    int* p;
    fun1(__ITERATOR_CATEGORY(p));
    my_stl::my_vector<int>::iterator it;
    fun1(__ITERATOR_CATEGORY(it));
    return 0;
}