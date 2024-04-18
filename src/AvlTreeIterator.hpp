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
        friend class AvlTree<T>;

    public:

        AvlTreeIterator();
        AvlTreeIterator(const AvlTreeIterator&) = default;
        ~AvlTreeIterator() = default;

        AvlTreeIterator& operator=(const AvlTreeIterator&) = default;
        AvlTreeIterator& operator++();
        AvlTreeIterator& operator++(int);
        AvlTreeIterator& operator--();
        AvlTreeIterator& operator--(int);

        T& operator*();
        const T& operator*() const;

        T& operator->();
        const T& operator->() const;

        bool operator==(const AvlTreeIterator& other) const;
        bool operator!=(const AvlTreeIterator& other) const;

    private:

        const detail::AvlTreeNode<T>* root_;
        detail::AvlTreeNode<T>* node_;
        explicit AvlTreeIterator(detail::AvlTreeNode<T>* node);
    };
}

template <typename T>
coursework::AvlTreeIterator<T>::AvlTreeIterator():
    root_(nullptr),
    node_(nullptr)
{}

template <typename T>
coursework::AvlTreeIterator<T>::AvlTreeIterator(detail::AvlTreeNode<T>* node):
    root_(node),
    node_(node)
{
    while (root_->parent_ != nullptr)
    {
        root_ = root_->parent_;
    }
}

template <typename T>
coursework::AvlTreeIterator<T>& coursework::AvlTreeIterator<T>::operator++()
{
    Node<T>* curr = this;

    while (curr->right_ == nullptr || curr->key_ < root_->key_)
    {
        if (curr == root_ && (root_->right_ == nullptr || curr->key_ < root_->key_))
        {
            return nullptr;
        }

        curr = curr->parent_;

        if (curr->key_ > root_->key_)
        {
            return curr;
        }
    }

    curr = curr->right_;
    curr = curr->begin();

    return curr;
}

template <typename T>
coursework::AvlTreeIterator<T>& coursework::AvlTreeIterator<T>::operator++(int)
{
    Node<T>* temp = AvlTreeIterator<T>(*this);
    operator++();
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
    return node_->key;
}

template <typename T>
const T& coursework::AvlTreeIterator<T>::operator->() const
{
    return node_->key;
}

template <typename T>
bool coursework::AvlTreeIterator<T>::operator==(const AvlTreeIterator& other) const
{
    return root_ == other.root_ && node_ == other.node_;
}

template <typename T>
bool coursework::AvlTreeIterator<T>::operator!=(const AvlTreeIterator& other) const
{
    return root_ != other.root_ || node_ != other.node_;
}

#endif // AVL_TREE_ITERATOR_HPP
