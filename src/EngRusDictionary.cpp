#include "EngRusDictionary.hpp"
#include "AvlTreeSetIterator.hpp"
#include <utility>

bool coursework::EngRusDictionary::insert(std::string key, std::string value)
{
    auto it = dict_.search(key);

    if (it == dict_.end())
    {
        dict_.insert(std::move(key), AvlTreeSet<std::string>());
        dict_.begin()->second.insert(std::move(value));
        return true;
    }

    if (it->second.search(value) != it->second.end())
    {
        return false;
    }

    it->second.insert(std::forward<std::string>(value));
    return true;
}

const coursework::EngRusDictionary::Subdict& coursework::EngRusDictionary::search(const std::string& rhs)
{
    return dict_.search(rhs)->second;
}

bool coursework::EngRusDictionary::remove(const std::string& rhs)
{
    return dict_.remove(rhs) != dict_.end();
}

