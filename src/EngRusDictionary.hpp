#ifndef ENG_RUS_DICTIONARY_HPP
#define ENG_RUS_DICTIONARY_HPP

#include <string>
#include "AvlTreeSet.hpp"
#include "AvlTreeMap.hpp"

namespace coursework
{
    class EngRusDictionary
    {
    public:

        using Subdict = AvlTreeSet<std::string>;
        using Dict = AvlTreeMap<std::string, Subdict>;

        EngRusDictionary() = default;

        EngRusDictionary(const EngRusDictionary&) = default;
        EngRusDictionary(EngRusDictionary&&) noexcept = default;

        EngRusDictionary& operator=(const EngRusDictionary&) = default;
        EngRusDictionary& operator=(EngRusDictionary&&) noexcept = default;

        ~EngRusDictionary() noexcept = default;

        Dict::Iterator begin();
        Dict::Iterator end();
        Dict::ConstIterator cbegin() const;
        Dict::ConstIterator cend() const;

        bool insert(std::string key, std::string value);
        const Subdict& search(const std::string& rhs) const;
        bool remove(const std::string& key, const std::string& value);

    private:

        Dict dict_;
    };
}

#endif // ENG_RUS_DICTIONARY_HPP
