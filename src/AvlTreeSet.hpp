#ifndef AVL_TREE_SET_HPP
#define AVL_TREE_SET_HPP

#include <initializer_list>
#include <utility>
#include "AvlTreeSetIterator.hpp"
#include "AvlTreeSetNode.hpp"
#include "IteratorStrategy.hpp"

namespace coursework
{
    template <typename T>
    class AvlTreeSet
    {
        using Node = detail::AvlTreeSetNode<T>;

    public:

        using Iterator = AvlTreeSetIterator<T>;
        using ConstIterator = Iterator;
        using ReverseIterator = AvlTreeSetIterator<T, detail::ReversedStrategy<detail::AvlTreeSetNode<T>>>;
        using ConstReverseIterator = ReverseIterator;

        AvlTreeSet();
        AvlTreeSet(const AvlTreeSet&) = delete;
        AvlTreeSet(AvlTreeSet&& rhs) noexcept;
        AvlTreeSet(std::initializer_list<T> rhs);
        template <typename InputIterator>
        AvlTreeSet(InputIterator begin, InputIterator end);

        AvlTreeSet& operator=(const AvlTreeSet&) = delete;
        AvlTreeSet& operator=(AvlTreeSet&& rhs) noexcept;

        virtual ~AvlTreeSet() noexcept;

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;
        ConstIterator cbegin() const;
        ConstIterator cend() const;

        ReverseIterator rbegin();
        ReverseIterator rend();
        ConstReverseIterator rbegin() const;
        ConstReverseIterator rend() const;
        ConstReverseIterator crbegin() const;
        ConstReverseIterator crend() const;

        Iterator insert(T&& rhs);
        Iterator search(const T& rhs) const;
        Iterator remove(const T& rhs);

    private:

        void clear(Node* rhs);
        Node* root_;
    };
}

template <typename T>
coursework::AvlTreeSet<T>::AvlTreeSet():
    root_(nullptr)
{}

template <typename T>
coursework::AvlTreeSet<T>::AvlTreeSet(AvlTreeSet&& rhs) noexcept:
    root_(rhs.root_)
{
    rhs.root_ = nullptr;
}

template <typename T>
coursework::AvlTreeSet<T>& coursework::AvlTreeSet<T>::operator=(AvlTreeSet&& rhs) noexcept
{
    if (this != &rhs)
    {
        clear(root_);
        root_ = rhs.root_;
        rhs.root_ = nullptr;
    }

    return *this;
}

template <typename T>
coursework::AvlTreeSet<T>::~AvlTreeSet() noexcept
{
    clear(root_);
}

template <typename T>
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::begin()
{
    Node* res = root_;

    while (res->left_ != nullptr)
    {
        res = res->left_;
    }

    return Iterator(root_, res);
}

template <typename T>
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::end()
{
    return Iterator(root_, nullptr);
}

template <typename T>
typename coursework::AvlTreeSet<T>::ConstIterator coursework::AvlTreeSet<T>::begin() const
{
    return begin();
}

template <typename T>
typename coursework::AvlTreeSet<T>::ConstIterator coursework::AvlTreeSet<T>::end() const
{
    return end();
}

template <typename T>
typename coursework::AvlTreeSet<T>::ConstIterator coursework::AvlTreeSet<T>::cbegin() const
{
    return begin();
}

template <typename T>
typename coursework::AvlTreeSet<T>::ConstIterator coursework::AvlTreeSet<T>::cend() const
{
    return end();
}

template <typename T>
typename coursework::AvlTreeSet<T>::ReverseIterator coursework::AvlTreeSet<T>::rbegin()
{
    Node* res = root_;

    while (res->right_ != nullptr)
    {
        res = res->right_;
    }

    return ReverseIterator(root_, res);
}

template <typename T>
typename coursework::AvlTreeSet<T>::ReverseIterator coursework::AvlTreeSet<T>::rend()
{
    return ReverseIterator(root_, nullptr);
}

template <typename T>
typename coursework::AvlTreeSet<T>::ConstReverseIterator coursework::AvlTreeSet<T>::rbegin() const
{
    return rbegin();
}

template <typename T>
typename coursework::AvlTreeSet<T>::ConstReverseIterator coursework::AvlTreeSet<T>::rend() const
{
    return rend();
}

template <typename T>
typename coursework::AvlTreeSet<T>::ConstReverseIterator coursework::AvlTreeSet<T>::crbegin() const
{
    return rbegin();
}

template <typename T>
typename coursework::AvlTreeSet<T>::ConstReverseIterator coursework::AvlTreeSet<T>::crend() const
{
    return rend();
}

template <typename T>
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::insert(T&& rhs)
{
    if (root_ == nullptr)
    {
        root_ = new Node(std::forward<T>(rhs));
        return begin();
    }

    Node* curr = root_;
    Node* prev = nullptr;

    while (curr != nullptr && rhs != curr->key_)
    {
        prev = curr;
        curr = rhs < curr->key_ ? curr->left_ : curr->right_;
    }

    if (curr != nullptr)
    {
        return end();
    }

    curr = new Node(std::forward<T>(rhs), prev);
    (curr->key_ < curr->parent_->key_ ? curr->parent_->left_ : curr->parent_->right_) = curr;

    root_ = root_->balance();
    return Iterator(root_, curr);
}

template <typename T>
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::search(const T& rhs) const
{
    Node* curr = root_;

    while (curr != nullptr && rhs != curr->key_)
    {
        curr = rhs < curr->key_ ? curr->left_ : curr->right_;
    }

    return Iterator(root_, curr);
}

template <typename T>
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::remove(const T& rhs)
{

}

template <typename T>
void coursework::AvlTreeSet<T>::clear(Node* rhs)
{
    if (rhs != nullptr)
    {
        clear(rhs->left_);
        clear(rhs->right_);
        delete rhs;
    }
}

#endif // AVL_TREE_SET_HPP
