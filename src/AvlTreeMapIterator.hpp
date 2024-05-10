#ifndef AVL_TREE_MAP_ITERATOR_HPP
#define AVL_TREE_MAP_ITERATOR_HPP

#include <iterator>
#include "AvlTreeMapNode.hpp"

namespace coursework
{
    template <typename T, typename U>
    class AvlTreeMap;

    template <typename T, typename U>
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

template <typename T, typename U>
coursework::AvlTreeMapIterator<T, U>::AvlTreeMapIterator():
    root_(nullptr),
    node_(nullptr)
{}

template <typename T, typename U>
coursework::AvlTreeMapIterator<T, U>::AvlTreeMapIterator(Node* root, Node* node):
    root_(root),
    node_(node)
{}

template <typename T, typename U>
coursework::AvlTreeMapIterator<T, U>& coursework::AvlTreeMapIterator<T, U>::operator++()
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
coursework::AvlTreeMapIterator<T, U> coursework::AvlTreeMapIterator<T, U>::operator++(int)
{
    AvlTreeMapIterator<T, U> temp(*this);
    ++(*this);
    return temp;
}

template <typename T, typename U>
coursework::AvlTreeMapIterator<T, U>& coursework::AvlTreeMapIterator<T, U>::operator--()
{

}

template <typename T, typename U>
coursework::AvlTreeMapIterator<T, U> coursework::AvlTreeMapIterator<T, U>::operator--(int)
{
    AvlTreeMapIterator<T, U> temp(*this);
    --(*this);
    return temp;
}

template <typename T, typename U>
typename coursework::AvlTreeMapIterator<T, U>::Data& coursework::AvlTreeMapIterator<T, U>::operator*()
{
    return node_->data_;
}

template <typename T, typename U>
const typename coursework::AvlTreeMapIterator<T, U>::Data& coursework::AvlTreeMapIterator<T, U>::operator*() const
{
    return node_->data_;
}

template <typename T, typename U>
typename coursework::AvlTreeMapIterator<T, U>::Data* coursework::AvlTreeMapIterator<T, U>::operator->()
{
    return &node_->data_;
}

template <typename T, typename U>
const typename coursework::AvlTreeMapIterator<T, U>::Data* coursework::AvlTreeMapIterator<T, U>::operator->() const
{
    return &node_->data_;
}

template <typename T, typename U>
bool coursework::AvlTreeMapIterator<T, U>::operator==(const AvlTreeMapIterator& rhs) const
{
    return root_ == rhs.root_ && node_ == rhs.node_;
}

template <typename T, typename U>
bool coursework::AvlTreeMapIterator<T, U>::operator!=(const AvlTreeMapIterator& rhs) const
{
    return !(*this == rhs);
}

#endif // AVL_TREE_MAP_ITERATOR_HPP
