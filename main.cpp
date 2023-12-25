#include <iostream>
#include "mySkipList.h"

int main() {
    // Seed the random number generator once at the start of the program
    srand(static_cast<unsigned>(time(nullptr)));
    // 创建一个最大层数为 5 的跳表实例
    SkipList<int, std::string> skiplist(5, 0.5);

    // 插入一些键值对
    skiplist.insert_element(1, "One");
    skiplist.insert_element(3, "Three");
    skiplist.insert_element(7, "Seven");
    skiplist.insert_element(5, "Five");
    skiplist.insert_element(9, "Nine");

    // 展示跳表
    skiplist.display_list();

    return 0;
}
