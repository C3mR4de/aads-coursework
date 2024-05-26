#ifndef ENG_RUS_DICTIONARY_TESTS_HPP
#define ENG_RUS_DICTIONARY_TESTS_HPP

#include "EngRusDictionary.hpp"

namespace coursework
{
    void testDictInsert(EngRusDictionary& dict, std::string key, std::string value);
    void testDictRemove(EngRusDictionary& dict, const std::string& key, const std::string& value);
}

#endif // ENG_RUS_DICTIONARY_TESTS_HPP
