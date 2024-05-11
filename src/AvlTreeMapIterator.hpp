#ifndef AVL_TREE_MAP_ITERATOR_HPP
#define AVL_TREE_MAP_ITERATOR_HPP

#include <iterator>
#include "AvlTreeMapNode.hpp"
#include "IteratorStrategy.hpp"

namespace coursework
{
    template <typename T, typename U>
    class AvlTreeMap;

    template <typename T, typename U, typename S = detail::StraightStrategy<detail::AvlTreeMapNode<T, U>>>
    class AvlTreeMapIterator: std::iterator<std::bidirectional_iterator_tag, const T>
    {
        friend class AvlTreeMap<T, U>;
        using Node = detail::AvlTreeMapNode<T, U>;
        using Data = Pair<const T, U>;

    public:

        AvlTreeMapIterator();
        AvlTreeMapIterator(const AvlTreeMapIterator&) = default;
        ~AvlTreeMapIterator() = default;

        AvlTreeMapIterator& operator=(const AvlTreeMapIterator&) = default;

        AvlTreeMapIterator& operator++();
        AvlTreeMapIterator operator++(int);
        AvlTreeMapIterator& operator--();
        AvlTreeMapIterator operator--(int);

        Data& operator*();
        const Data& operator*() const;

        Data* operator->();
        const Data* operator->() const;

        bool operator==(const AvlTreeMapIterator& rhs) const;
        bool operator!=(const AvlTreeMapIterator& rhs) const;

    private:

        Node* root_;
        Node* node_;
        explicit AvlTreeMapIterator(Node* root, Node* node);
    };
}

template <typename T, typename U, typename S>
coursework::AvlTreeMapIterator<T, U, S>::AvlTreeMapIterator():
    root_(nullptr),
    node_(nullptr)
{}

template <typename T, typename U, typename S>
coursework::AvlTreeMapIterator<T, U, S>::AvlTreeMapIterator(Node* root, Node* node):
    root_(root),
    node_(node)
{}

template <typename T, typename U, typename S>
coursework::AvlTreeMapIterator<T, U, S>& coursework::AvlTreeMapIterator<T, U, S>::operator++()
{
    /*
    Node* curr = node_;

    while (curr->right_ == nullptr || curr->data_.key_ < node_->data_.key_)
    {
        if (curr == root_ && (root_->right_ == nullptr || curr->data_.key_ < node_->data_.key_))
        {
            node_ = nullptr;
            return *this;
        }

        curr = curr->parent_;

        if (curr->data_.key_ > node_->data_.key_)
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

    node_ = curr;*/
    node_ = S::next(root_, node_);
    return *this;
}

template <typename T, typename U, typename S>
coursework::AvlTreeMapIterator<T, U, S> coursework::AvlTreeMapIterator<T, U, S>::operator++(int)
{
    AvlTreeMapIterator<T, U, S> temp(*this);
    ++(*this);
    return temp;
}

template <typename T, typename U, typename S>
coursework::AvlTreeMapIterator<T, U, S>& coursework::AvlTreeMapIterator<T, U, S>::operator--()
{
    node_ = S::prev(root_, node_);
    return *this;
}

template <typename T, typename U, typename S>
coursework::AvlTreeMapIterator<T, U, S> coursework::AvlTreeMapIterator<T, U, S>::operator--(int)
{
    AvlTreeMapIterator<T, U, S> temp(*this);
    --(*this);
    return temp;
}

template <typename T, typename U, typename S>
typename coursework::AvlTreeMapIterator<T, U, S>::Data& coursework::AvlTreeMapIterator<T, U, S>::operator*()
{
    return node_->data_;
}

template <typename T, typename U, typename S>
const typename coursework::AvlTreeMapIterator<T, U, S>::Data& coursework::AvlTreeMapIterator<T, U, S>::operator*() const
{
    return node_->data_;
}

template <typename T, typename U, typename S>
typename coursework::AvlTreeMapIterator<T, U, S>::Data* coursework::AvlTreeMapIterator<T, U, S>::operator->()
{
    return &node_->data_;
}

template <typename T, typename U, typename S>
const typename coursework::AvlTreeMapIterator<T, U, S>::Data* coursework::AvlTreeMapIterator<T, U, S>::operator->() const
{
    return &node_->data_;
}

template <typename T, typename U, typename S>
bool coursework::AvlTreeMapIterator<T, U, S>::operator==(const AvlTreeMapIterator& rhs) const
{
    return root_ == rhs.root_ && node_ == rhs.node_;
}

template <typename T, typename U, typename S>
bool coursework::AvlTreeMapIterator<T, U, S>::operator!=(const AvlTreeMapIterator& rhs) const
{
    return !(*this == rhs);
}

#endif // AVL_TREE_MAP_ITERATOR_HPP
