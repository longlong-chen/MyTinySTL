/*
 * @Author: chenlonglong 
 * @Date: 2023-04-08 10:37:04 
 * @Last Modified by: chenlonglong
 * @Last Modified time: 2023-04-08 10:48:57
 */

#include<iostream>
#include<vector>

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

int main() {
    std::cout << "The result of official example: \n";
    official_example();

    std::cout << "The result of expliciting allocator: \n";
    explicit_allocator(); 

    return 0;
}

/**
 * Output: 
 * The result of official example: 
 * The contents of fifth are: 16 2 77 29
 * The result of expliciting allocator: 
 * The contents of fifth are: 16 2 77 29
*/