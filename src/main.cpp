#include "DictionaryList.hpp"
#include <iostream>

int main()
{
    coursework::DictionaryList<int> list;

    list.insert(5);
    list.insert(15);
    list.insert(10);
    list.insert(-3);

    for (auto& i : list)
    {
        std::cout << i << "\n";
    }

    std::cout << "Hello World\n";

    return 0;
}
