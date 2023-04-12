/*
 * @Author: chenlonglong 
 * @Date: 2023-04-12 11:40:47 
 * @Last Modified by:   chenlonglong 
 * @Last Modified time: 2023-04-12 11:40:47 
 */
#include "my_vector.h"

void my_vector_example() {
    my_stl::my_vector<int> first;                                
    my_stl::my_vector<int> second (4,100);                       
    my_stl::my_vector<int> third (4); 
    my_stl::my_vector<int> fifth (third);                       
    my_stl::my_vector<int> sixth {1, 2, 3 , 4}; 
    my_stl::my_vector<int> (std::move(sixth)); 
    my_stl::my_vector<my_stl::my_vector<int>> seventh;
}

int main() {
    my_vector_example();
    return 0;
}
