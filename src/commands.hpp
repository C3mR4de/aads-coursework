#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "EngRusDictionary.hpp"
#include <iosfwd>

namespace coursework
{
    namespace cmd
    {
        void insert(std::istream& in, std::ostream& out, EngRusDictionary& dict);
        void search(std::istream& in, std::ostream& out, const EngRusDictionary& dict);
        void remove(std::istream& in, std::ostream& out, EngRusDictionary& dict);
    }
}

#endif // COMMANDS_HPP
