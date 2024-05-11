#ifndef AVL_TREE_SET_ITERATOR_HPP
#define AVL_TREE_SET_ITERATOR_HPP

#include <iterator>
#include "AvlTreeSetNode.hpp"
#include "IteratorStrategy.hpp"

namespace coursework
{
    template <typename T>
    class AvlTreeSet;

    template <typename T, typename S = detail::StraightStrategy<detail::AvlTreeSetNode<T>>>
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

template <typename T, typename S>
coursework::AvlTreeSetIterator<T, S>::AvlTreeSetIterator():
    root_(nullptr),
    node_(nullptr)
{}

template <typename T, typename S>
coursework::AvlTreeSetIterator<T, S>::AvlTreeSetIterator(Node* root, Node* node):
    root_(root),
    node_(node)
{}

template <typename T, typename S>
coursework::AvlTreeSetIterator<T, S>& coursework::AvlTreeSetIterator<T, S>::operator++()
{
    node_ = S::next(root_, node_);
    return *this;
}

template <typename T, typename S>
coursework::AvlTreeSetIterator<T, S> coursework::AvlTreeSetIterator<T, S>::operator++(int)
{
    AvlTreeSetIterator<T, S> temp(*this);
    ++(*this);
    return temp;
}

template <typename T, typename S>
coursework::AvlTreeSetIterator<T, S>& coursework::AvlTreeSetIterator<T, S>::operator--()
{
    node_ = S::prev(root_, node_);
    return *this;
}

template <typename T, typename S>
coursework::AvlTreeSetIterator<T, S> coursework::AvlTreeSetIterator<T, S>::operator--(int)
{
    AvlTreeSetIterator<T, S> temp(*this);
    --(*this);
    return temp;
}

template <typename T, typename S>
const T& coursework::AvlTreeSetIterator<T, S>::operator*() const
{
    return node_->key_;
}

template <typename T, typename S>
const T* coursework::AvlTreeSetIterator<T, S>::operator->() const
{
    return &node_->key_;
}

template <typename T, typename S>
bool coursework::AvlTreeSetIterator<T, S>::operator==(const AvlTreeSetIterator& rhs) const
{
    return root_ == rhs.root_ && node_ == rhs.node_;
}

template <typename T, typename S>
bool coursework::AvlTreeSetIterator<T, S>::operator!=(const AvlTreeSetIterator& rhs) const
{
    return !(*this == rhs);
}

#endif // AVL_TREE_SET_ITERATOR_HPP
