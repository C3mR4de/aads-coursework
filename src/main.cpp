#include <iostream>
#include <functional>
#include <limits>
#include "commands.hpp"

int main()
{
    using namespace coursework;

    EngRusDictionary dict;

    AvlTreeMap<std::string, std::function<void(std::istream&, std::ostream&)>> commands;

    using namespace std::placeholders;
    commands.insert("INSERT", std::bind(cmd::insert, _1, _2, std::ref(dict)));
    commands.insert("SEARCH", std::bind(cmd::search, _1, _2, std::cref(dict)));
    commands.insert("REMOVE", std::bind(cmd::remove, _1, _2, std::ref(dict)));

    std::string cmd;

    while (std::cin >> cmd)
    {
        auto it = commands.search(cmd);

        if (it == commands.end())
        {
            std::cout << "<INVALID_COMMAND>\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            it->second(std::cin, std::cout);
        }
    }

    return 0;
}
