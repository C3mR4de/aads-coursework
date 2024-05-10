#ifndef AVL_TREE_SET_HPP
#define AVL_TREE_SET_HPP

#include <initializer_list>
#include <utility>
#include "AvlTreeSetIterator.hpp"
#include "AvlTreeSetNode.hpp"

namespace coursework
{
    template <typename T>
    class AvlTreeSet
    {
        using Node = detail::AvlTreeSetNode<T>;

    public:

        using Iterator = AvlTreeSetIterator<T>;
        using ConstIterator = Iterator;

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

        Iterator rbegin();
        Iterator rend();
        ConstIterator rbegin() const;
        ConstIterator rend() const;
        ConstIterator crbegin() const;
        ConstIterator crend() const;

        Iterator insert(T&& key);
        Iterator search(const T& key) const;
        Iterator remove(const T& key);

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
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::insert(T&& key)
{
    if (root_ == nullptr)
    {
        root_ = new Node(std::forward<T>(key));
        return begin();
    }

    Node* curr = root_;
    Node* prev = nullptr;

    while (curr != nullptr && key != curr->key_)
    {
        prev = curr;
        curr = key < curr->key_ ? curr->left_ : curr->right_;
    }

    if (curr != nullptr)
    {
        return end();
    }

    curr = new Node(std::forward<T>(key), prev);
    (key < curr->parent_->key_ ? curr->parent_->left_ : curr->parent_->right_) = curr;

    root_ = root_->balance();
    return Iterator(root_, curr);
}

template <typename T>
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::search(const T& key) const
{
    Node* curr = root_;

    while (curr != nullptr && key != curr->data_.key_)
    {
        curr = key < curr->key_ ? curr->left_ : curr->right_;
    }

    return Iterator(root_, curr);
}

template <typename T>
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::remove(const T& key)
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
