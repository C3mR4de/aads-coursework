#ifndef AVL_TREE_SET_TESTS_HPP
#define AVL_TREE_SET_TESTS_HPP

#include <iostream>
#include <cmath>
#include "AvlTreeSet.hpp"

namespace coursework
{
    template <typename T>
    void testSetOutput(const AvlTreeSet<T>& tree)
    {
        for (const auto& i : tree)
        {
            std::cout << i << " ";
        }

        std::cout << "\n";
    }

    template <typename T>
    std::size_t getHeight(const detail::AvlTreeSetNode<T>* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return 1 + std::max(getHeight(node->left_), getHeight(node->right_));
    }

    template <typename T>
    bool checkBalance(const detail::AvlTreeSetNode<T>* node)
    {
        if (node == nullptr)
        {
            return true;
        }

        int lh = getHeight(node->left_);
        int rh = getHeight(node->right_);

        return std::abs(rh - lh) <= 1 && checkBalance(node->left_) && checkBalance(node->right_);
    }

    template <typename T>
    void testSetInsert(AvlTreeSet<T>& tree, T value)
    {
        tree.insert(std::move(value));
        testSetOutput(tree);
        std::cout << checkBalance(tree.getRoot()) << "\n";
    }

    template <typename T>
    void testSetRemove(AvlTreeSet<T>& tree, T value)
    {
        tree.remove(std::move(value));
        testSetOutput(tree);
        std::cout << checkBalance(tree.getRoot()) << "\n";
    }
}

#endif // AVL_TREE_SET_TESTS_HPP
