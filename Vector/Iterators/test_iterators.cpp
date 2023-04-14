#include "my_vector.h"

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

int main() {
    test_begin_end();
    test_cbegin_cend();
    return 0;
}