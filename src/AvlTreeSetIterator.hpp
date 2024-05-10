#ifndef AVL_TREE_SET_ITERATOR_HPP
#define AVL_TREE_SET_ITERATOR_HPP

#include <iterator>
#include "AvlTreeSetNode.hpp"

namespace coursework
{
    template <typename T>
    class AvlTreeSet;

    template <typename T>
    class AvlTreeSetIterator: std::iterator<std::bidirectional_iterator_tag, const T>
    {
        friend class AvlTreeSet<T>;
        using Node = detail::AvlTreeSetNode<T>;

    public:

        AvlTreeSetIterator();
        AvlTreeSetIterator(const AvlTreeSetIterator&) = default;
        ~AvlTreeSetIterator() = default;

        AvlTreeSetIterator& operator=(const AvlTreeSetIterator&) = default;

        AvlTreeSetIterator& operator++();
        AvlTreeSetIterator operator++(int);
        AvlTreeSetIterator& operator--();
        AvlTreeSetIterator operator--(int);

        const T& operator*() const;
        const T* operator->() const;

        bool operator==(const AvlTreeSetIterator& rhs) const;
        bool operator!=(const AvlTreeSetIterator& rhs) const;

    private:

        Node* root_;
        Node* node_;
        explicit AvlTreeSetIterator(Node* root, Node* node);
    };
}

template <typename T>
coursework::AvlTreeSetIterator<T>::AvlTreeSetIterator():
    root_(nullptr),
    node_(nullptr)
{}

template <typename T>
coursework::AvlTreeSetIterator<T>::AvlTreeSetIterator(Node* root, Node* node):
    root_(root),
    node_(node)
{}

template <typename T>
coursework::AvlTreeSetIterator<T>& coursework::AvlTreeSetIterator<T>::operator++()
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
coursework::AvlTreeSetIterator<T> coursework::AvlTreeSetIterator<T>::operator++(int)
{
    AvlTreeSetIterator<T> temp(*this);
    ++(*this);
    return temp;
}

template <typename T>
coursework::AvlTreeSetIterator<T>& coursework::AvlTreeSetIterator<T>::operator--()
{

}

template <typename T>
coursework::AvlTreeSetIterator<T> coursework::AvlTreeSetIterator<T>::operator--(int)
{
    AvlTreeSetIterator<T> temp(*this);
    --(*this);
    return temp;
}

template <typename T>
const T& coursework::AvlTreeSetIterator<T>::operator*() const
{
    return node_->key_;
}

template <typename T>
const T* coursework::AvlTreeSetIterator<T>::operator->() const
{
    return &node_->key_;
}

template <typename T>
bool coursework::AvlTreeSetIterator<T>::operator==(const AvlTreeSetIterator& rhs) const
{
    return root_ == rhs.root_ && node_ == rhs.node_;
}

template <typename T>
bool coursework::AvlTreeSetIterator<T>::operator!=(const AvlTreeSetIterator& rhs) const
{
    return !(*this == rhs);
}

#endif // AVL_TREE_SET_ITERATOR_HPP
