#ifndef AVL_TREE_ITERATOR_HPP
#define AVL_TREE_ITERATOR_HPP

#include <iterator>
#include "AvlTreeNode.hpp"

namespace coursework
{
    template <typename T, typename U>
    class AvlTree;

    template <typename T, typename U>
    class AvlTreeIterator: std::iterator<std::bidirectional_iterator_tag, const T>
    {
        friend class AvlTree<T, U>;
        using Node = detail::AvlTreeNode<T, U>;
        using Data = Pair<const T, U>;

    public:

        AvlTreeIterator();
        AvlTreeIterator(const AvlTreeIterator&) = default;
        ~AvlTreeIterator() = default;

        AvlTreeIterator& operator=(const AvlTreeIterator&) = default;

        AvlTreeIterator& operator++();
        AvlTreeIterator operator++(int);
        AvlTreeIterator& operator--();
        AvlTreeIterator operator--(int);

        Data& operator*();
        const Data& operator*() const;

        Data& operator->();
        const Data& operator->() const;

        bool operator==(const AvlTreeIterator& rhs) const;
        bool operator!=(const AvlTreeIterator& rhs) const;

    private:

        Node* root_;
        Node* node_;
        explicit AvlTreeIterator(Node* root, Node* node);
    };
}

template <typename T, typename U>
coursework::AvlTreeIterator<T, U>::AvlTreeIterator():
    root_(nullptr),
    node_(nullptr)
{}

template <typename T, typename U>
coursework::AvlTreeIterator<T, U>::AvlTreeIterator(Node* root, Node* node):
    root_(root),
    node_(node)
{}

template <typename T, typename U>
coursework::AvlTreeIterator<T, U>& coursework::AvlTreeIterator<T, U>::operator++()
{
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

    node_ = curr;
    return *this;
}

template <typename T, typename U>
coursework::AvlTreeIterator<T, U> coursework::AvlTreeIterator<T, U>::operator++(int)
{
    AvlTreeIterator<T, U> temp(*this);
    ++(*this);
    return temp;
}

template <typename T, typename U>
coursework::AvlTreeIterator<T, U>& coursework::AvlTreeIterator<T, U>::operator--()
{

}

template <typename T, typename U>
coursework::AvlTreeIterator<T, U> coursework::AvlTreeIterator<T, U>::operator--(int)
{
    AvlTreeIterator<T, U> temp(*this);
    --(*this);
    return temp;
}

template <typename T, typename U>
typename coursework::AvlTreeIterator<T, U>::Data& coursework::AvlTreeIterator<T, U>::operator*()
{
    return node_->data_;
}

template <typename T, typename U>
const typename coursework::AvlTreeIterator<T, U>::Data& coursework::AvlTreeIterator<T, U>::operator*() const
{
    return node_->data_;
}

template <typename T, typename U>
typename coursework::AvlTreeIterator<T, U>::Data& coursework::AvlTreeIterator<T, U>::operator->()
{
    return node_->data_;
}

template <typename T, typename U>
const typename coursework::AvlTreeIterator<T, U>::Data& coursework::AvlTreeIterator<T, U>::operator->() const
{
    return node_->data_;
}

template <typename T, typename U>
bool coursework::AvlTreeIterator<T, U>::operator==(const AvlTreeIterator& rhs) const
{
    return root_ == rhs.root_ && node_ == rhs.node_;
}

template <typename T, typename U>
bool coursework::AvlTreeIterator<T, U>::operator!=(const AvlTreeIterator& rhs) const
{
    return !(*this == rhs);
}

#endif // AVL_TREE_ITERATOR_HPP
