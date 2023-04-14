## Iterators 中的一些记录

### begin()和cbegin()的异同：

* `iterator`、`const_iterator`的作用：遍历容器内的元素，并访问这些元素的值。`iterator`可以改变元素值，但`const_iterator`不可以改变。
* `const_iterator`可用于`const vector`或非`const vector`，它自身的值可以修改，可以指向其它元素，但不能修改它指向的元素值。
* `cbegin()`和`cend()`是C++11新增的，它们返回一个`const`的迭代器，不能用于修改元素。

### C++ 为何引入常量迭代器cbegin()和cend?

总的来说就是用什么方法保证迭代器内容的常量化。以往写迭代器的`for循环`:

~~~c
vector<MyType> v;
typedef vector<MyType>::iterator iter;
for(iter it = v.begin(); it != v.end(); ++it) {} 
~~~

如果想让迭代器是一个常量：

~~~c
for(const iter it = v.begin(); it != v.end(); ++it) {} 
~~~

会报错! `const iter it` 会导致`++it`编译失败，因为`it`是常量无法`++`。所以，需要实现一个可以`++`，但是还能够保证不能改变`it`内容的类型，于是`container::const_iterator`出现了。上面的代码可以写为：

~~~c
vector<MyType> v;
typedef vector<MyType>::const_iterator iter;
for(iter it = v.begin(); it != v.end(); ++it) {} 
~~~

别高兴的太早，解决上面问题后，问题又来了！那就是`auto`。`auto`可以去推导初始化的变量类型，并且常常用于迭代器上，因为迭代器的写法确实很冗长，完全可以用`auto`来代替。但是，如果使用：

~~~c
for(auto it = v.begin(); it != v.end(); ++it) {}
~~~

显然无法获得一个`const_iterator`。

所以，这个时候我们就需要一个返回`const_iterator`类型的函数，所以`cbegin`和`cend`就孕育而生。

参考：

* [C++ 为何引入常量迭代器cbegin()和cend?](https://www.zhihu.com/question/508478510)
* [提案文档](./A Proposal to Improve const_iterator Use from C++0X Containers.pdf)