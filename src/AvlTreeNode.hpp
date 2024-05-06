#ifndef AVL_TREE_NODE_HPP
#define AVL_TREE_NODE_HPP

#include <utility>

namespace coursework
{
    namespace detail
    {
        template <typename T>
        struct AvlTreeNode
        {
            T key_;

            AvlTreeNode* parent_;
            AvlTreeNode* left_;
            AvlTreeNode* right_;

            int factor_;

            AvlTreeNode(T&& key, AvlTreeNode* parent = nullptr,
                                 AvlTreeNode* left = nullptr,
                                 AvlTreeNode* right = nullptr);
        };
    }
}

template<typename  T>
coursework::detail::AvlTreeNode<T>::AvlTreeNode(T&& key, AvlTreeNode* parent, AvlTreeNode* left, AvlTreeNode* right):
    key_(std::forward<T>(key)),
    parent_(parent),
    left_(left),
    right_(right),
    factor_(0)
{}

#endif // AVL_TREE_NODE_HPP
