#include "AvlTree.hpp"
#include "DictionaryList.hpp"
#include <string>
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

    coursework::DictionaryList<int> list2(list);

    list2.insert(1000);

    coursework::DictionaryList<int> list3 = list2;

    list3.erase(5);

    for (const auto& i : list)
    {
        std::cout << i << "\n";
    }

    std::cout << "\n";

    for (const auto& i : list2)
    {
        std::cout << i << "\n";
    }

    std::cout << "\n";

    for (const auto& i : list3)
    {
        std::cout << i << "\n";
    }

    std::cout << "\n";

    coursework::DictionaryList<std::string> strlist;

    strlist.insert("fefe");
    strlist.insert("ratatata");
    strlist.insert("rapapa");

    coursework::DictionaryList<std::string> strlist2(strlist);

    strlist2.insert("tatar");

    for (const auto& i : strlist)
    {
        std::cout << i << "\n";
    }

    std::cout << "\n";

    for (const auto& i : strlist2)
    {
        std::cout << i << "\n";
    }

    std::cout << "\n";

    std::cout << "Hello World\n";

    coursework::AvlTree<std::string, int> tree;

    tree.insert("dsd", 3);
    tree.insert("dadad", 16);
    tree.insert("super", -10);
    tree.insert("auto", 100);

    for (auto& i : tree)
    {
        std::cout << i.key_ << " " << i.value_ << "\n";
    }

    return 0;
}
