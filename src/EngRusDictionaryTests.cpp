#include "EngRusDictionaryTests.hpp"
#include <iostream>

void coursework::testDictInsert(EngRusDictionary& dict, std::string key, std::string value)
{
    dict.insert(std::move(key), std::move(value));

    for (const auto& i : dict)
    {
        for (const auto& j : i.second)
        {
            std::cout << i.first << " - " << j << "\n";
        }
    }

    std::cout << "\n";
}

void coursework::testDictRemove(EngRusDictionary& dict, const std::string& key, const std::string& value)
{
    dict.remove(key, value);

    for (const auto& i : dict)
    {
        for (const auto& j : i.second)
        {
            std::cout << i.first << " - " << j << "\n";
        }
    }

    std::cout << "\n";
}
