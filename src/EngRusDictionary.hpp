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

        EngRusDictionary(const EngRusDictionary&) = delete;
        EngRusDictionary(EngRusDictionary&& rhs) noexcept = default;

        EngRusDictionary& operator=(const EngRusDictionary&) = delete;
        EngRusDictionary& operator=(EngRusDictionary&& rhs) noexcept = default;

        ~EngRusDictionary() noexcept = default;

        bool insert(std::string&& key, std::string&& value);
        const Subdict& search(const std::string& rhs);
        bool remove(const std::string& rhs);

    private:

        Dict dict_;
    };
}

#endif // ENG_RUS_DICTIONARY_HPP
