#include "my_vector.h"
#include <typeinfo>
#include "iterator.h"
#include <utility> // std::make_pair
#include <map>     // std::map
#include <string>  // std::string

void test_begin_end() {
    my_stl::my_vector<int> myvector = {1, 2, 3, 4, 5};
    std::cout << "myvector contains: \n";
    for(auto it = myvector.begin(); it != myvector.end(); ++it) {
        std::cout << "Old element: " << *it;
        (*it) += 1;
        std::cout << "; New element: " << *it;
        std::cout << '\n';
    }
}

void test_cbegin_cend() {
    my_stl::my_vector<int> myconstvector = {1, 2, 3, 4, 5};
    std::cout << "myconstvector contains: \n";
    for(my_stl::my_vector<int>::const_iterator it = myconstvector.cbegin(); it != myconstvector.cend(); ++it) {
        std::cout << "Old element: " << *it;
        // (*it) += 1;
        // std::cout << "; New element: " << *it;
        std::cout << '\n';
    }
}

/* Test `reverse_iterator` constructor */
/* Also, test `operator*()` and `operator++()` */
void test_construct_reverse_iterator() {
    my_stl::my_vector<int> myvector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    typedef my_stl::my_vector<int>::iterator iter_type;

    iter_type from(myvector.begin());

    iter_type until(myvector.end());

    my_stl::reverse_iterator<iter_type> rev_until(from);

    my_stl::reverse_iterator<iter_type> rev_from(until);

    std::cout << "myvector:";
    while(rev_from != rev_until) {
        std::cout << ' ' << *rev_from++;
    }
    std::cout << '\n';
}
/**
 * Output: 
 * initializer list constructor
 * myvector: 10 9 8 7 6 5 4 3 2 1
*/

/**
 * Output: 
 * initializer list constructor
 * myvector: 1 2 3 4 5 6 7 8 9 10
*/
void test_reverse_iterator_base() {
    my_stl::my_vector<int> myvector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    typedef my_stl::my_vector<int>::iterator iter_type;

    my_stl::reverse_iterator<iter_type> rev_end(myvector.begin());
    my_stl::reverse_iterator<iter_type> rev_begin(myvector.end());

    std::cout << "myvector:";
    for(iter_type it = rev_end.base(); it != rev_begin.base(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

/* reverse_iterator::operator+ example or free operator+ */
void test_reverse_iterator_operator_add() {
    my_stl::my_vector<int> myvector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    typedef my_stl::my_vector<int>::iterator iter_type;

    my_stl::reverse_iterator<iter_type> rev_it;

    // rev_it = myvector.rbegin() + 3; 
    rev_it = 3 + myvector.rbegin();

    std::cout << "The fourth element from the end is: " << *rev_it << '\n';
}
/**
 * Output:
 * initializer list constructor
 * operator+ or free operator+ 
 * The fourth element from the end is: 6
*/

/* reverse_iterator::operator++(int) example */
void test_reverse_iterator_operator_add_add() {
    my_stl::my_vector<int> myvector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    typedef my_stl::my_vector<int>::iterator iter_type;

    iter_type from(myvector.begin());

    iter_type until(myvector.end());

    my_stl::reverse_iterator<iter_type> rev_until(from);

    my_stl::reverse_iterator<iter_type> rev_from(until);

    std::cout << "myvector:";
    while(rev_from != rev_until) {
        std::cout << ' ' << *rev_from;
        ++rev_from;
    }
    std::cout << '\n';
}
/**
 * initializer list constructor
 * myvector: 9 8 7 6 5 4 3 2 1 0
*/

/* reverse_iterator::operator+= example */
void test_reverse_iterator_operator_add_equal() {
    my_stl::my_vector<int> myvector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    typedef my_stl::my_vector<int>::iterator iter_type;

    my_stl::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

    rev_iterator += 2;

    std::cout << "The third element from the end is: " << *rev_iterator << '\n';
}
/**
 * Output:
 * initializer list constructor
 * The third element from the end is: 7
*/

/* reverse_iterator::operator- example */
void test_reverse_iterator_operator_minus() {
    my_stl::my_vector<int> myvector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    typedef my_stl::my_vector<int>::iterator iter_type;

    my_stl::reverse_iterator<iter_type> rev_iterator;

    rev_iterator = myvector.rend() - 3;

    std::cout << "myvector.rend()-3 points to: " << *rev_iterator << '\n';
}
/**
 * Output:
 * initializer list constructor
 * operator- 
 * myvector.rend()-3 points to: 2
*/

void test_reverse_iterator_operator_minus_minus() {
    my_stl::my_vector<int> myvector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    typedef my_stl::my_vector<int>::iterator iter_type;

    my_stl::reverse_iterator<iter_type> rev_begin(myvector.end());
    my_stl::reverse_iterator<iter_type> rev_end(myvector.begin());

    my_stl::reverse_iterator<iter_type> rev_iterator = rev_begin;
    while(rev_iterator != rev_end) {
        std::cout << *rev_iterator++ << ' ';
    }
    std::cout << '\n';

    while(rev_iterator != rev_begin) {
        std::cout << *(--rev_iterator) << ' ';
    }
    std::cout << '\n';
}
/**
 * Output:
 * 9 8 7 6 5 4 3 2 1 0 
 * 0 1 2 3 4 5 6 7 8 9
*/

void test_reverse_iterator_operator_minus_equal() {
    my_stl::my_vector<int> myvector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    typedef my_stl::my_vector<int>::iterator iter_type;

    my_stl::reverse_iterator<iter_type> rev_iterator = myvector.rend();

    rev_iterator -= 4;

    std::cout << "rev_iterator now points to: " << *rev_iterator << '\n';
}
/**
 * Output:
 * initializer list constructor
 * rev_iterator now points to: 3
*/

/* reverse_iterator::operator-> example */
void test_reverse_iterator_operator_arrow() {
    std::map<int,std::string> numbers;
    numbers.insert (std::make_pair(1,"one"));
    numbers.insert (std::make_pair(2,"two"));
    numbers.insert (std::make_pair(3,"three"));

    typedef std::map<int,std::string>::iterator map_iter;

    std::reverse_iterator<map_iter> rev_end(numbers.begin());

    std::reverse_iterator<map_iter> rev_iterator(numbers.end());

    for(; rev_iterator != rev_end; ++rev_iterator) {
        std::cout << rev_iterator->first << ' ' << rev_iterator->second << '\n';
    }
}
/**
 * Output:
 * 3 three
 * 2 two
 * 1 one
*/

/* reverse_iterator::operator[] example */
void test_reverse_iterator_operator_square_bracks() {
    my_stl::my_vector<int> myvector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    typedef my_stl::my_vector<int>::iterator iter_type;

    my_stl::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

    std::cout << "The fourth element from the end is: " << rev_iterator[3] << '\n';
}
/**
 * Output:
 * initializer list constructor
 * The fourth element from the end is: 6
*/

/* operator- on reverse_iterator */
void test_minus_on_reverse_iterator_operator() {
    my_stl::my_vector<int> myvector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    my_stl::reverse_iterator<my_stl::my_vector<int>::iterator> from, until;

    from = myvector.rbegin();
    until = myvector.rend();

    std::cout << "myvector has " << (until - from) << " elements.\n";
}
/**
 * Output:
 * initializer list constructor
 * myvector has free operator-
 * 10 elements.
*/

int main() {
    test_begin_end();
    test_cbegin_cend();
    if (typeid(std::iterator_traits<int*>::iterator_category)==typeid(std::random_access_iterator_tag))
        std::cout << "int* is a random-access iterator";
    test_construct_reverse_iterator();
    test_reverse_iterator_base();
    test_reverse_iterator_operator_add();
    test_reverse_iterator_operator_add_add();
    test_reverse_iterator_operator_add_equal();
    test_reverse_iterator_operator_minus();
    test_reverse_iterator_operator_minus_minus();
    test_reverse_iterator_operator_minus_equal();
    test_reverse_iterator_operator_arrow();
    test_reverse_iterator_operator_square_bracks();
    test_minus_on_reverse_iterator_operator();
    return 0;
}