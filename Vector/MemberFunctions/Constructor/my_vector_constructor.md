## 一些记录

### 实现思路与流程：

* 内存分配器先调用#include<memory>的`allocator`，之后在实现
* 实现流程按`cplusplus.com`网站接口顺序实现
* 测试则按网站提供的例子当作测试用例，并对比结果差异

### 文件说明：

`test_constructor.cpp`：《STL源码剖析》中测试vector构造和内存管理的代码，之后作为测试样例使用；

`test_my_vector_constructor.cpp`: 使用网站例子构造测试样例，首先显示的尝试了如何显示的使用`allocator`；

### 待解决：

`range constructor`: 