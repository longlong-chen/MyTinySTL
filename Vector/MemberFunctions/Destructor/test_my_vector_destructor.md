## 旨在检查构造与析构的内存使用情况

使用工具：valgrind
语法实例：valgrind --leak-check=full ./test

### 测试流程

* Case 1 : 不实现析构函数，看每种构造函数是否造成内存泄漏
    * `my_stl::my_vector<int> first`: 否
    * `my_stl::my_vector<int> second (4,100)`: 是
    * `my_stl::my_vector<int> third (4)`: 是
    * `my_stl::my_vector<int> sixth {1, 2, 3 , 4}`: 是
    * `my_stl::my_vector<my_stl::my_vector<int>> seventh`: 否

    初步结论：只要填充数据就会内存泄漏
* Case 2 : 实现析构函数，看每种构造函数是否造成内存泄漏
    * `my_stl::my_vector<int> first`: 否
    * `my_stl::my_vector<int> second (4,100)`: 否
    * `my_stl::my_vector<int> third (4)`: 否
    * `my_stl::my_vector<int> sixth {1, 2, 3 , 4}`: 否
    * `my_stl::my_vector<my_stl::my_vector<int>> seventh`: 否 

    初步结论：暂未出现内存泄漏情况
* Case 3 : 实现析构函数，一次性调用所有测试构造函数是否造成内存泄漏
    * 增添 `my_stl::my_vector<int> fifth (third)` 和 `my_stl::my_vector<int> (std::move(sixth))`

    结论：暂未出现内存泄漏问题

### 缺点

    实现是直接遍历每一个对象进行资源回收，这样会造成效率上的大大折扣，从《STL源码剖析》中可知如果是一些对象无关痛痒且对象较多则默认什么就不做就可以避免内存泄漏。所以，下一步可以尝试引入类型萃取去进一步优化。
