#include <iostream>
#include "mySkipList.h"

int main() {
    // Seed the random number generator once at the start of the program
    srand(static_cast<unsigned>(time(nullptr)));
    // 创建一个最大层数为 5 的跳表实例
    SkipList<int, std::string> skiplist(5, 0.5);

    // insert some elements
    skiplist.insert_element(1, "One");
    skiplist.insert_element(3, "Three");
    skiplist.insert_element(7, "Seven");
    skiplist.insert_element(5, "Five");
    skiplist.insert_element(9, "Nine");

    // two ways to display
    skiplist.display_list();

    skiplist.full_display_list();

    std::cout << "DELETE" << std::endl;

    // delete some elements
    skiplist.delete_element(7);
    skiplist.delete_element(3);

    // two ways to display
    skiplist.display_list();

    skiplist.full_display_list();

    return 0;
}
