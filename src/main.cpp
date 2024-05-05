#include "DictionaryList.hpp"
#include <iostream>

int main()
{
    coursework::DictionaryList<int> list;

    list.insert(5);
    list.insert(15);
    list.insert(10);
    list.insert(-3);
    list.insert(20);
    list.insert(-100);

    list.erase(10);
    list.erase(15);

    std::cout << (list.search(30) != list.end() ? "success\n" : "fail\n");
    std::cout << (list.search(10) != list.end() ? "success\n" : "fail\n");
    std::cout << (list.search(20) != list.end() ? "success\n" : "fail\n");

    for (const auto& i : list)
    {
        std::cout << i << "\n";
    }

    std::cout << "Hello World\n";

    return 0;
}
