#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main() {
    int i;
    vector<int> iv(2, 9);
    cout << "size=" << iv.size() << endl; // 2
    cout << "capacity=" << iv.capacity() << endl; // 3

    iv.push_back(1);
    cout << "size=" << iv.size() << endl; // 3
    cout << "capacity=" << iv.capacity() << endl; //4

    iv.push_back(2);
    cout << "size=" << iv.size() << endl; // 4
    cout << "capacity=" << iv.capacity() << endl; //4

    iv.push_back(3);
    cout << "size=" << iv.size() << endl; // 5
    cout << "capacity=" << iv.capacity() << endl; // 8

    iv.push_back(4);
    cout << "size=" << iv.size() << endl; // 6
    cout << "capacity=" << iv.capacity() << endl; //8

    for(i = 0; i < iv.size(); ++i) {
        cout << iv[i] << ' '; // 9 9 1 2 3 4
    }
    cout << endl;

    iv.push_back(5);

    cout << "size=" << iv.size() << endl; // 7
    cout << "capacity=" << iv.capacity() << endl; // 8
    for(i = 0; i < iv.size(); ++i) {
        cout << iv[i] << ' '; // 9 9 1 2 3 4 5
    }
    cout << endl;

    iv.pop_back();
    iv.pop_back();
    cout << "size=" << iv.size() << endl; // 5
    cout << "capacity=" << iv.capacity() << endl; // 8

    iv.pop_back();
    cout << "size=" << iv.size() << endl; // 4
    cout << "capacity=" << iv.capacity() << endl; // 8

    vector<int>::iterator ivite = find(iv.begin(), iv.end(), 1);
    if(ivite != iv.end()) iv.erase(ivite);

    cout << "size=" << iv.size() << endl; // 3
    cout << "capacity=" << iv.capacity() << endl; // 8
    for(i = 0; i < iv.size(); ++i) {
        cout << iv[i] << ' '; // 9 9 2
    }
    cout << endl;

    ivite = find(iv.begin(), iv.end(), 2); 
    // if(ivite != iv.end()) iv.insert(ivite, 3, 7);
    iv.insert(ivite, 3, 7);

    cout << "size=" << iv.size() << endl; // 6
    cout << "capacity=" << iv.capacity() << endl; // 8
    for(i = 0; i < iv.size(); ++i) {
        cout << iv[i] << ' '; // 9 9 7 7 7 2
    }
    cout << endl;

    iv.clear();
    cout << "size=" << iv.size() << endl; // 0
    cout << "capacity=" << iv.capacity() << endl; // 8

    //插入时能传iv.end()吗？
    iv.insert(iv.end(), 1, 1);
    cout << "size=" << iv.size() << endl; // 1
    cout << "capacity=" << iv.capacity() << endl; // 8 

    //能删除iv.end()吗？
    iv.erase(iv.end()); // 报错：段错误（核心已转储）
    cout << "size=" << iv.size() << endl; 
    cout << "capacity=" << iv.capacity() << endl;  

    return 0;
}

//插入时能传iv.end()吗？OK ==> 62 更改

/**
 * 总结：
 * 当当前capacity已经沾满是，vector会以2倍的方式扩充capacity
 * capacity直到结束不会变小
 * 可以做自我实现的测试用例
*/

/**
 * c:82 ==> 练习gdb调试
 * ulimit -c 
 * 0
 * ulimit -c 1
 * 一块512B 够用
 * 段错误不产生cora文件
 * cat /proc/sys/kernel/core_pattern
 * |/usr/share/apport/apport -p%p -s%s -c%c -d%d -P%P -u%u -g%g -- %E
 * 原因：原来设置为|/usr/share/apport/apport %p %s %c %P的话，文件的结果会被Linux的一个进程apport 吞掉，拿去检查是不是系统的bug，所以看不到core文件了
 * 解决方案：如果想产生core文件，需要关闭这个进程
 * sudo service apport stop
 * chenlonglong 不在 sudoers 文件中。此事将被报告 权限不够
 * su
 * sudo service apport stop
 * su chenlonglong
 * cat /proc/sys/kernel/core_pattern
 * cora
 * 
*/