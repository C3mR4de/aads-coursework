#include "AvlTreeSet.hpp"
#include "AvlTreeMap.hpp"
#include "EngRusDictionary.hpp"
#include <iostream>
#include <string>

#include "AvlTreeSetTests.hpp"

int main()
{
    using namespace coursework;

    /*
    AvlTreeSet<int> set;

    set.insert(3);
    set.insert(5);
    set.insert(20);
    set.insert(10);
    set.insert(-100);
    set.insert(-1000);

    set.remove(-1000);
    set.remove(20);
    set.remove(5);

    for (auto i = set.begin(); i != set.end(); ++i)
    {
        std::cout << *i << "\n";
    }

    std::cout << "\n";

    for (auto i = set.cbegin(); i != set.cend(); ++i)
    {
        std::cout << *i << "\n";
    }

    std::cout << "\n";

    for (auto i = set.rbegin(); i != set.rend(); ++i)
    {
        std::cout << *i << "\n";
    }

    std::cout << "\n";

    for (auto i = set.crbegin(); i != set.crend(); ++i)
    {
        std::cout << *i << "\n";
    }

    std::cout << "\n";

    for (const auto& i : set)
    {
        std::cout << i << "\n";
    }

    std::cout << "\n";

    for (auto& i : set)
    {
        std::cout << i << "\n";
    }

    std::cout << "\n";

    AvlTreeSet<std::string> setstr;

    std::string existing = "existing";

    setstr.insert("ferg");
    setstr.insert("rapapa");
    setstr.insert("parampampam");
    setstr.insert("aramzamzam");
    setstr.insert(std::move(existing));

    setstr.remove("aramzamzam");
    setstr.remove("parampampam");

    for (auto i = setstr.begin(); i != setstr.end(); ++i)
    {
        std::cout << *i << "\n";
    }

    std::cout << "\n";

    for (auto i = setstr.rbegin(); i != setstr.rend(); ++i)
    {
        std::cout << *i << "\n";
    }

    std::cout << "\n";

    for (const auto& i : setstr)
    {
        std::cout << i << "\n";
    }

    std::cout << "\n";

    for (auto& i : setstr)
    {
        std::cout << i << "\n";
    }

    std::cout << "\n";
    */

    AvlTreeSet<int> set;

    testSetOutput(set);
    testSetInsert(set, 15);
    testSetInsert(set, 15);
    testSetInsert(set, 23);
    testSetInsert(set, 23);
    testSetInsert(set, 13);
    testSetInsert(set, 13);
    testSetInsert(set, 14);
    testSetInsert(set, 14);
    testSetInsert(set, 25);
    testSetInsert(set, 25);
    testSetInsert(set, 18);
    testSetInsert(set, 18);
    testSetInsert(set, 16);
    testSetInsert(set, 16);
    testSetInsert(set, 17);
    testSetInsert(set, 17);

    AvlTreeSet<int> set2 = std::move(set);

    testSetRemove(set2, 15);
    testSetRemove(set2, 15);
    testSetRemove(set2, 13);
    testSetRemove(set2, 13);
    testSetRemove(set2, 25);
    testSetRemove(set2, 25);
    testSetRemove(set2, 18);
    testSetRemove(set2, 18);
    testSetRemove(set2, 16);
    testSetRemove(set2, 16);
    testSetRemove(set2, 17);
    testSetRemove(set2, 17);
    testSetRemove(set2, 23);
    testSetRemove(set2, 23);
    testSetRemove(set2, 14);
    testSetRemove(set2, 14);

    AvlTreeSet<int> set3;
    set3 = std::move(set2);

    testSetInsert(set3, 15);
    testSetInsert(set3, 23);
    testSetInsert(set3, 13);
    testSetInsert(set3, 14);
    testSetInsert(set3, 25);
    testSetInsert(set3, 18);
    testSetInsert(set3, 16);
    testSetInsert(set3, 17);

    testSetRemove(set3, 17);
    testSetInsert(set3, 17);

    testSetRemove(set3, 17);
    testSetInsert(set3, 17);

    testSetRemove(set3, 17);
    testSetInsert(set3, 17);

    testSetRemove(set3, 17);
    testSetInsert(set3, 17);

    testSetRemove(set3, 17);
    testSetInsert(set3, 17);

    testSetRemove(set3, 15);
    testSetRemove(set3, 16);
    testSetRemove(set3, 17);
    testSetRemove(set3, 18);
    testSetRemove(set3, 23);
    testSetRemove(set3, 25);
    testSetRemove(set3, 13);
    testSetRemove(set3, 14);
    testSetRemove(set3, 25);

    // testSetInsert(set3, 17);
    // testSetInsert(set3, 16);
    // testSetInsert(set3, 15);
    // testSetInsert(set3, 14);
    // testSetInsert(set3, 13);
    // testSetInsert(set3, 12);
    // testSetInsert(set3, 11);
    // testSetInsert(set3, 10);

    // AvlTreeSet<int> set4;
    //
    // testSetInsert(set4, 15);
    // testSetInsert(set4, 12);
    // testSetInsert(set4, 20);
    // testSetInsert(set4, 21);
    // testSetInsert(set4, 18);
    // testSetInsert(set4, 22);
    // testSetInsert(set4, 19);

    AvlTreeSet<int> set5;

    testSetInsert(set5, 17);
    testSetInsert(set5, 18);
    testSetInsert(set5, 19);
    testSetInsert(set5, 20);
    testSetInsert(set5, 21);
    testSetInsert(set5, 22);
    testSetInsert(set5, 23);
    testSetInsert(set5, 24);
    /*
    AvlTreeMap<std::string, int> map;

    std::string existing2 = "existing2";

    map.insert("dsd", 3);
    map.insert("dadad", 16);
    map.insert("super", -10);
    map.insert("auto", 100);
    map.insert("-----fwfeeauto", 2000);
    map.insert("русский текст", 0);
    map.insert("русский текст222", 123);
    map.insert(std::move(existing2), 12345);

    map.remove("dsd");
    map.remove("русский текст222");

    for (auto i = map.begin(); i != map.end(); ++i)
    {
        std::cout << i->first << " " << i->second << "\n";
    }

    for (auto i = map.cbegin(); i != map.cend(); ++i)
    {
        std::cout << i->first << " " << i->second << "\n";
    }

    for (auto& i : map)
    {
        std::cout << i.first << " " << i.second << "\n";
    }

    for (const auto& i : map)
    {
        std::cout << i.first << " " << i.second << "\n";
    }

    for (auto i = map.rbegin(); i != map.rend(); ++i)
    {
        std::cout << i->first << " " << i->second << "\n";
    }

    for (auto i = map.crbegin(); i != map.crend(); ++i)
    {
        std::cout << i->first << " " << i->second << "\n";
    }

    auto res = map.search("dsd");
    std::cout << (res != map.end() ? res->second : 0) << "\n";

    for (auto& i : map)
    {
        i.second = 4324;
        std::cout << i.first << " " << i.second << "\n";
    }

    EngRusDictionary engrus;

    std::cout << engrus.insert("good", "хорошо") << "\n";
    std::cout << engrus.insert("good", "хороший") << "\n";
    std::cout << engrus.insert("good", "товар") << "\n";

    std::cout << engrus.insert("bad", "плохо") << "\n";
    std::cout << engrus.insert("direct", "направление") << "\n";
    std::cout << engrus.insert("direct", "направление") << "\n";

    for (auto it = engrus.search("good").cbegin(); it != engrus.search("good").cend(); ++it)
    {
        std::cout << *it << "\n";
    }

    std::cout << engrus.remove("good") << "\n";
    std::cout << engrus.remove("good") << "\n";
    */

    return 0;
}
