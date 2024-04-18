#ifndef AVL_TREE_NODE_HPP
#define AVL_TREE_NODE_HPP

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

            AvlTreeNode(const T& key, AvlTreeNode* parent = nullptr,
                                      AvlTreeNode* left = nullptr,
                                      AvlTreeNode* right = nullptr);
        };

        template<typename  T>
        AvlTreeNode<T>::AvlTreeNode(const T& key, AvlTreeNode* parent, AvlTreeNode* left, AvlTreeNode* right):
            key_(key),
            parent_(parent),
            left_(left),
            right_(right),
            factor_(0)
        {}
    }
}

#endif
