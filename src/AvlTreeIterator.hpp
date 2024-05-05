#ifndef AVL_TREE_ITERATOR_HPP
#define AVL_TREE_ITERATOR_HPP

#include "AvlTreeNode.hpp"
#include <iterator>

namespace coursework
{
    template <typename T>
    class AvlTree;

    template <typename T>
    class AvlTreeIterator: std::iterator<std::bidirectional_iterator_tag, T>
    {
    public:

        friend class AvlTree<T>;
        using Node = detail::AvlTreeNode<T>;

        AvlTreeIterator();
        AvlTreeIterator(const AvlTreeIterator&) = default;
        ~AvlTreeIterator() = default;

        AvlTreeIterator& operator=(const AvlTreeIterator&) = default;

        AvlTreeIterator& operator++();
        AvlTreeIterator operator++(int);
        AvlTreeIterator& operator--();
        AvlTreeIterator operator--(int);

        T& operator*();
        const T& operator*() const;

        T& operator->();
        const T& operator->() const;

        bool operator==(const AvlTreeIterator& rhs) const;
        bool operator!=(const AvlTreeIterator& rhs) const;

    private:

        Node* root_;
        Node* node_;
        explicit AvlTreeIterator(Node* root, Node* node);
    };
}

template <typename T>
coursework::AvlTreeIterator<T>::AvlTreeIterator():
    root_(nullptr),
    node_(nullptr)
{}

template <typename T>
coursework::AvlTreeIterator<T>::AvlTreeIterator(Node* root, Node* node):
    root_(root),
    node_(node)
{}

template <typename T>
coursework::AvlTreeIterator<T>& coursework::AvlTreeIterator<T>::operator++()
{
    Node* curr = node_;

    while (curr->right_ == nullptr || curr->key_ < node_->key_)
    {
        if (curr == root_ && (root_->right_ == nullptr || curr->key_ < node_->key_))
        {
            node_ = nullptr;
            return *this;
        }

        curr = curr->parent_;

        if (curr->key_ > node_->key_)
        {
            node_ = curr;
            return *this;
        }
    }

    curr = curr->right_;

    while (curr->left_ != nullptr)
    {
        curr = curr->left_;
    }

    node_ = curr;
    return *this;
}

template <typename T>
coursework::AvlTreeIterator<T> coursework::AvlTreeIterator<T>::operator++(int)
{
    AvlTreeIterator<T> temp(*this);
    ++(*this);
    return temp;
}

template <typename T>
T& coursework::AvlTreeIterator<T>::operator*()
{
    return node_->key_;
}

template <typename T>
const T& coursework::AvlTreeIterator<T>::operator*() const
{
    return node_->key_;
}

template <typename T>
T& coursework::AvlTreeIterator<T>::operator->()
{
    return node_->key_;
}

template <typename T>
const T& coursework::AvlTreeIterator<T>::operator->() const
{
    return node_->key_;
}

template <typename T>
bool coursework::AvlTreeIterator<T>::operator==(const AvlTreeIterator& rhs) const
{
    return root_ == rhs.root_ && node_ == rhs.node_;
}

template <typename T>
bool coursework::AvlTreeIterator<T>::operator!=(const AvlTreeIterator& rhs) const
{
    return !(*this == rhs);
}

#endif // AVL_TREE_ITERATOR_HPP
