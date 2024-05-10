#include "AvlTreeMap.hpp"
#include "DictionaryList.hpp"
#include <string>
#include <iostream>

int main()
{
    coursework::AvlTreeMap<std::string, int> tree;

    tree.insert("dsd", 3);
    tree.insert("dadad", 16);
    tree.insert("super", -10);
    tree.insert("auto", 100);
    tree.insert("-----fwfeeauto", 2000);

    for (auto& i : tree)
    {
        std::cout << i.key_ << " " << i.value_ << "\n";
    }

    auto res = tree.search("dsd");
    std::cout << (res != tree.end() ? res->value_ : 0) << "\n";

    return 0;
}
