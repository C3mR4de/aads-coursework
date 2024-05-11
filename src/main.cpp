#include "AvlTreeMap.hpp"
#include "AvlTreeSet.hpp"
#include <string>
#include <iostream>

int main()
{
    coursework::AvlTreeSet<int> set;

    set.insert(3);
    set.insert(5);
    set.insert(20);
    set.insert(10);
    set.insert(-100);
    set.insert(-1000);

    for (const auto& i : set)
    {
        std::cout << i << "\n";
    }

    for (auto& i : set)
    {
        std::cout << i << "\n";
    }

    coursework::AvlTreeSet<std::string> setstr;

    std::string existing = "existing";

    setstr.insert("ferg");
    setstr.insert("rapapa");
    setstr.insert("parampampam");
    setstr.insert("aramzamzam");
    setstr.insert(std::move(existing));

    for (const auto& i : setstr)
    {
        std::cout << i << "\n";
    }

    for (auto& i : setstr)
    {
        std::cout << i << "\n";
    }

    coursework::AvlTreeMap<std::string, int> map;

    map.insert("dsd", 3);
    map.insert("dadad", 16);
    map.insert("super", -10);
    map.insert("auto", 100);
    map.insert("-----fwfeeauto", 2000);
    map.insert("а че такое?", 0);

    for (const auto& i : map)
    {
        std::cout << i.key_ << " " << i.value_ << "\n";
    }

    /*
    for (auto i = map.crbegin(); i != map.crend(); --i)
    {
        std::cout << i->key_ << " " << i->value_ << "\n";
    }
    */

    for (auto& i : map)
    {
        i.value_ = 4324;
        std::cout << i.key_ << " " << i.value_ << "\n";
    }

    auto res = map.search("dsd");
    std::cout << (res != map.end() ? res->value_ : 0) << "\n";

    return 0;
}
