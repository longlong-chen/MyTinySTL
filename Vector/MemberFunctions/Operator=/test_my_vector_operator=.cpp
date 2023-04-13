/*
 * @Author: chenlonglong 
 * @Date: 2023-04-13 10:45:31 
 * @Last Modified by: chenlonglong
 * @Last Modified time: 2023-04-13 11:04:26
 */
#include "my_vector.h"

// text my_vector's operator=
void my_vector_example() {
    my_stl::my_vector<int> first(4, 100);
    my_stl::my_vector<int> second = first;
    my_stl::my_vector<int> third = {1, 2, 3 , 4};
    my_stl::my_vector<int> fourth = std::move(first);                                 
}

int main() {
    my_vector_example();    
    return 0;
}