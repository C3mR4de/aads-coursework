#ifndef AVL_TREE_CONST_ITERATOR_HPP
#define AVL_TREE_CONST_ITERATOR_HPP

#include "AvlTreeNode.hpp"
#include <iterator>

namespace coursework
{
    template <typename T>
    class AvlTree;

    template <typename T>
    class AvlTreeConstIterator: std::iterator<std::bidirectional_iterator_tag, T>
    {
        friend class AvlTree<T>;

    public:

        AvlTreeConstIterator();
        AvlTreeConstIterator(const AvlTreeConstIterator&) = default;
        ~AvlTreeConstIterator() = default;

        const AvlTreeConstIterator& operator=(const AvlTreeConstIterator&) = default;
        const AvlTreeConstIterator& operator++();
        const AvlTreeConstIterator& operator++(int);
        const AvlTreeConstIterator& operator--();
        const AvlTreeConstIterator& operator--(int);

        const T& operator*() const;
        const T& operator->() const;

        bool operator==(const AvlTreeConstIterator& other) const;
        bool operator!=(const AvlTreeConstIterator& other) const;

    private:

        const detail::AvlTreeNode<T>* root_;
        const detail::AvlTreeNode<T>* node_;
        explicit AvlTreeConstIterator(const detail::AvlTreeNode<T>* node);
    };
}

template <typename T>
coursework::AvlTreeConstIterator<T>::AvlTreeConstIterator():
    root_(nullptr),
    node_(nullptr)
{}

template <typename T>
coursework::AvlTreeConstIterator<T>::AvlTreeConstIterator(const detail::AvlTreeNode<T>* node):
    root_(node),
    node_(node)
{
    while (root_->parent_ != nullptr)
    {
        root_ = root_->parent_;
    }
}

template <typename T>
const coursework::AvlTreeConstIterator<T>& coursework::AvlTreeConstIterator<T>::operator++()
{
    detail::AvlTreeNode<T>* curr = this;

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
const coursework::AvlTreeConstIterator<T>& coursework::AvlTreeConstIterator<T>::operator++(int)
{
    detail::AvlTreeNode<T>* temp = AvlTreeConstIterator<T>(*this);
    operator++();
    return temp;
}

template <typename T>
const T& coursework::AvlTreeConstIterator<T>::operator*() const
{
    return node_->key_;
}

template <typename T>
const T& coursework::AvlTreeConstIterator<T>::operator->() const
{
    return node_->key;
}

template <typename T>
bool coursework::AvlTreeConstIterator<T>::operator==(const AvlTreeConstIterator& other) const
{
    return root_ == other.root_ && node_ == other.node_;
}

template <typename T>
bool coursework::AvlTreeConstIterator<T>::operator!=(const AvlTreeConstIterator& other) const
{
    return root_ != other.root_ || node_ != other.node_;
}

#endif // AVL_TREE_CONST_ITERATOR_HPP

