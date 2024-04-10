#ifndef AVL_TREE_NODE_HPP
#define AVL_TREE_NODE_HPP

namespace coursework
{
    template <typename T>
    struct Node
    {
        T key_;

        Node* parent_;
        Node* left_;
        Node* right_;

        int factor_;

        Node(const T& key, Node* parent = nullptr,
                             Node* left = nullptr,
                             Node* right = nullptr);
    };

    template<typename  T>
    Node<T>::Node(const T& key, Node* parent, Node* left, Node* right):
        key_(key),
        parent_(parent),
        left_(left),
        right_(right),
        factor_(0)
    {}
}

#endif
