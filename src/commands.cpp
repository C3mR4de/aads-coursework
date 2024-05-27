#include "commands.hpp"
#include <ostream>

void coursework::cmd::insert(std::istream& in, std::ostream& out, EngRusDictionary& dict)
{
    std::string key;
    std::string value;
    in >> key >> value;

    bool res = dict.insert(std::move(key), std::move(value));

    if (!res)
    {
        out << "<INVALID_COMMAND>\n";
    }
}

void coursework::cmd::search(std::istream& in, std::ostream& out, const EngRusDictionary& dict)
{
    std::string key;
    in >> key;

    auto res = dict.search(key);

    if (res.begin() == res.end())
    {
        out << "<INVALID_COMMAND>\n";
        return;
    }

    for (const auto& i : res)
    {
        out << i << "\n";
    }
}

void coursework::cmd::remove(std::istream& in, std::ostream& out, EngRusDictionary& dict)
{
    std::string key;
    std::string value;
    in >> key >> value;

    bool res = dict.remove(key, value);

    if (!res)
    {
        out << "<INVALID_COMMAND>\n";
    }
}
