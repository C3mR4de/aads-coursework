#include "EngRusDictionary.hpp"
#include <iostream>

#include "AvlTreeSetTests.hpp"
#include "AvlTreeMapTests.hpp"
#include "EngRusDictionaryTests.hpp"

int main()
{
    using namespace coursework;

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

    AvlTreeSet<int> setCopy(set);

    testSetInsert(setCopy, 50000);
    testSetInsert(setCopy, 1000000);
    testSetInsert(set, 30);

    AvlTreeSet<int> setCopy2;
    setCopy2 = setCopy;

    testSetInsert(setCopy2, 123456789);
    testSetInsert(setCopy, 987654321);

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
    testSetRemove(set2, 30);
    testSetRemove(set2, 30);

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

    testSetInsert(set3, 17);
    testSetInsert(set3, 16);
    testSetInsert(set3, 15);
    testSetInsert(set3, 14);
    testSetInsert(set3, 13);
    testSetInsert(set3, 12);
    testSetInsert(set3, 11);
    testSetInsert(set3, 10);

    AvlTreeSet<int> set4;

    testSetInsert(set4, 15);
    testSetInsert(set4, 12);
    testSetInsert(set4, 20);
    testSetInsert(set4, 21);
    testSetInsert(set4, 18);
    testSetInsert(set4, 22);
    testSetInsert(set4, 19);

    AvlTreeSet<int> set5;

    testSetInsert(set5, 17);
    testSetInsert(set5, 18);
    testSetInsert(set5, 19);
    testSetInsert(set5, 20);
    testSetInsert(set5, 21);
    testSetInsert(set5, 22);
    testSetInsert(set5, 23);
    testSetInsert(set5, 24);

    AvlTreeMap<std::string, int> map;

    testMapOutput(map);

    std::string existing1 = "existing1";

    testMapInsert(map, existing1, 10);

    std::cout << existing1 << "\n";

    std::string existing2 = "existing2";

    testMapInsert(map, std::move(existing2), 14);

    std::cout << existing2 << "\n";

    testMapInsert(map, std::string("object"), 200);
    testMapInsert(map, std::string("object"), 200);
    testMapInsert(map, std::string("move"), 500);
    testMapInsert(map, std::string("move"), 500);
    testMapInsert(map, std::string("русский текст"), -12);
    testMapInsert(map, std::string("русский текст"), -12);
    testMapInsert(map, std::string("avl tree"), -50);
    testMapInsert(map, std::string("avl tree"), -50);
    testMapInsert(map, std::string("a"), 1);
    testMapInsert(map, std::string("a"), 2);
    testMapInsert(map, std::string("b"), 2);
    testMapInsert(map, std::string("b"), 1);

    testMapRemove(map, std::string("b"));
    testMapRemove(map, std::string("move"));
    testMapRemove(map, std::string("русский текст"));
    testMapRemove(map, std::string("avl tree"));

    EngRusDictionary dict;

    testDictInsert(dict, "good", "хороший");
    testDictInsert(dict, "good", "хороший");
    testDictInsert(dict, "good", "товар");
    testDictInsert(dict, "good", "товар");
    testDictInsert(dict, "bad", "плохой");
    testDictInsert(dict, "bad", "плохой");
    testDictInsert(dict, "direct", "направление");
    testDictInsert(dict, "direct", "направление");

    testDictRemove(dict, "good", "хороший");
    testDictRemove(dict, "good", "хороший");
    testDictRemove(dict, "direct", "направления");
    testDictRemove(dict, "directs", "направление");
    testDictRemove(dict, "direct", "направление");

    return 0;
}
