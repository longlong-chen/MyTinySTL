/*
 * @Author: chenlonglong 
 * @Date: 2023-04-08 10:37:04 
 * @Last Modified by: chenlonglong
 * @Last Modified time: 2023-04-11 17:28:55
 */

#include<iostream>
#include<vector>
#include "my_vector.h"

// cplusplus.com officail code
void official_example() {
    // constructors used in the same order as described above:
    std::vector<int> first;                                // empty vector of ints
    std::vector<int> second (4,100);                       // four ints with value 100
    std::vector<int> third (second.begin(),second.end());  // iterating through second
    std::vector<int> fourth (third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

    std::cout << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

// explicit use 'allocator'
void explicit_allocator() {
    // constructors used in the same order as described above:
    std::vector<int, std::allocator<int>> first;                                // empty vector of ints
    std::vector<int, std::allocator<int>> second (4,100);                       // four ints with value 100
    std::vector<int, std::allocator<int>> third (second.begin(),second.end());  // iterating through second
    std::vector<int, std::allocator<int>> fourth (third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

    std::cout << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

// text my_vector's constructor
void my_vector_example() {
    // constructors used in the same order as described above:
    my_stl::my_vector<int> first;                                // empty vector of ints
    my_stl::my_vector<int> second (4,100);                       // four ints with value 100
    my_stl::my_vector<int> third (4); 
    std::vector<int> tmp (4,100);
    // my_stl::my_vector<int> fourth (tmp.begin(), tmp.end());  // iterating through tmp
    my_stl::my_vector<int> fifth (third);                       // a copy of third
    my_stl::my_vector<int> sixth {1, 2, 3 , 4}; 
    my_stl::my_vector<int> (std::move(sixth));
    
}

int main() {
    // std::cout << "The result of official example: \n";
    // official_example();

    // std::cout << "The result of expliciting allocator: \n";
    // explicit_allocator(); 
    my_vector_example();

    return 0;
}

/**
 * Output: 
 * The result of official example: 
 * The contents of fifth are: 16 2 77 29
 * The result of expliciting allocator: 
 * The contents of fifth are: 16 2 77 29
*/