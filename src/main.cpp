#include "AvlTree.hpp"
#include <iostream>

int main()
{
    coursework::AvlTree<int> tree;

    tree.insert(5);
    tree.insert(4);
    tree.insert(-1000);
    tree.insert(9);
    tree.insert(8);
    tree.insert(10);
    tree.insert(13);
    tree.insert(199);

    for (const auto& i : tree)
    {
        std::cout << i << '\n';
    }

    std::cout << "Hello World\n";

    return 0;
}
