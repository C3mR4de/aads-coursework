#ifndef AVL_TREE_MAP_TESTS_HPP
#define AVL_TREE_MAP_TESTS_HPP

#include <iostream>
#include <cmath>
#include "AvlTreeMap.hpp"

namespace coursework
{
    template <typename T, typename U>
    void testMapOutput(const AvlTreeMap<T, U>& tree)
    {
        for (const auto& i : tree)
        {
            std::cout << i.first << " " << i.second << " ";
        }

        std::cout << "\n";
    }

    template <typename T, typename U>
    std::size_t getHeight(const detail::AvlTreeMapNode<T, U>* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return 1 + std::max(getHeight(node->left_), getHeight(node->right_));
    }

    template <typename T, typename U>
    bool checkBalance(const detail::AvlTreeMapNode<T, U>* node)
    {
        if (node == nullptr)
        {
            return true;
        }

        int lh = getHeight(node->left_);
        int rh = getHeight(node->right_);

        return std::abs(rh - lh) <= 1 && checkBalance(node->left_) && checkBalance(node->right_);
    }

    template <typename T, typename U>
    void testMapInsert(AvlTreeMap<T, U>& tree, T key, U value)
    {
        tree.insert(std::move(key), std::move(value));
        testMapOutput(tree);
        std::cout << checkBalance(tree.getRoot()) << "\n";
    }

    template <typename T, typename U>
    void testMapRemove(AvlTreeMap<T, U>& tree, T key, U value)
    {
        tree.remove(std::move(key), std::move(value));
        testMapOutput(tree);
        std::cout << checkBalance(tree.getRoot()) << "\n";
    }
}

#endif // AVL_TREE_MAP_TESTS_HPP
