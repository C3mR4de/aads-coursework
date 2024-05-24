#include "EngRusDictionary.hpp"
#include "AvlTreeSetIterator.hpp"
#include <utility>

bool coursework::EngRusDictionary::insert(std::string&& key, std::string&& value)
{
    auto it = dict_.search(key);

    if (it == dict_.end())
    {
        dict_.insert(std::forward<std::string>(key), AvlTreeSet<std::string>());
        dict_.begin()->value_.insert(std::forward<std::string>(value));
        return true;
    }

    if (it->value_.search(value) != it->value_.end())
    {
        return false;
    }

    it->value_.insert(std::forward<std::string>(value));
    return true;
}

const coursework::EngRusDictionary::Subdict& coursework::EngRusDictionary::search(const std::string& rhs)
{
    return dict_.search(rhs)->value_;
}

bool coursework::EngRusDictionary::remove(const std::string& rhs)
{
    return dict_.remove(rhs) != dict_.end();
}

