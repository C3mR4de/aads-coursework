#ifndef AVL_TREE_NODE_HPP
#define AVL_TREE_NODE_HPP

#include <utility>
#include "Pair.hpp"

namespace coursework
{
    namespace detail
    {
        template <typename T, typename U>
        struct AvlTreeNode
        {
            Pair<const T, U> data_;

            AvlTreeNode* parent_;
            AvlTreeNode* left_;
            AvlTreeNode* right_;

            int factor_;

            AvlTreeNode(const T& key,
                        U&& value,
                        AvlTreeNode* parent = nullptr,
                        AvlTreeNode* left = nullptr,
                        AvlTreeNode* right = nullptr);
        };
    }
}

template<typename T, typename U>
coursework::detail::AvlTreeNode<T, U>::AvlTreeNode(const T& key,
                                                   U&& value,
                                                   AvlTreeNode* parent,
                                                   AvlTreeNode* left,
                                                   AvlTreeNode* right):
    data_(key, std::forward<U>(value)),
    parent_(parent),
    left_(left),
    right_(right),
    factor_(0)
{}

#endif // AVL_TREE_NODE_HPP
