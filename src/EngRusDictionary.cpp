#include "EngRusDictionary.hpp"
#include "AvlTreeSetIterator.hpp"
#include <utility>

coursework::EngRusDictionary::Dict::Iterator coursework::EngRusDictionary::begin()
{
    return dict_.begin();
}

coursework::EngRusDictionary::Dict::Iterator coursework::EngRusDictionary::end()
{
    return dict_.end();
}

bool coursework::EngRusDictionary::insert(std::string key, std::string value)
{
    auto it = dict_.search(key);

    if (it == dict_.end())
    {
        auto res = dict_.insert(std::move(key), Subdict())->second.insert(std::move(value));
        return res != dict_.begin()->second.end();
    }

    return it->second.insert(std::forward<std::string>(value)) != it->second.end();
}

const coursework::EngRusDictionary::Subdict& coursework::EngRusDictionary::search(const std::string& rhs)
{
    return dict_.search(rhs)->second;
}

bool coursework::EngRusDictionary::remove(const std::string& key, const std::string& value)
{
    auto it = dict_.search(key);

    if (it == dict_.end())
    {
        return false;
    }

    return it->second.remove(value) != it->second.end();
}
