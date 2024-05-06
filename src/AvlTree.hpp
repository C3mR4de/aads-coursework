#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <initializer_list>
#include <utility>
#include "AvlTreeIterator.hpp"
#include "AvlTreeNode.hpp"

namespace coursework
{
    template <typename T, typename U>
    class AvlTree
    {
        using Node = detail::AvlTreeNode<T, U>;
        using Data = Pair<T, U>;

    public:

        using Iterator = AvlTreeIterator<T, U>;
        using ConstIterator = AvlTreeIterator<T, const U>;

        AvlTree();
        AvlTree(const AvlTree& rhs) = delete;
        AvlTree(AvlTree&& rhs) noexcept;
        AvlTree(std::initializer_list<T> rhs);
        template <typename InputIterator>
        AvlTree(InputIterator begin, InputIterator end);

        AvlTree& operator=(const AvlTree& rhs) = delete;
        AvlTree& operator=(AvlTree&& rhs) noexcept;

        ~AvlTree() noexcept;

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

        Iterator insert(const T& key, U&& value);

    private:

        void clear(Node* rhs);
        Node* root_;
    };
}

template <typename T, typename U>
coursework::AvlTree<T, U>::AvlTree():
    root_(nullptr)
{}

template <typename T, typename U>
coursework::AvlTree<T, U>::AvlTree(AvlTree&& rhs) noexcept:
    root_(rhs.root_)
{
    rhs.root_ = nullptr;
}

template <typename T, typename U>
coursework::AvlTree<T, U>& coursework::AvlTree<T, U>::operator=(AvlTree&& rhs) noexcept
{
    if (this != &rhs)
    {
        clear(root_);
        root_ = rhs.root_;
        rhs.root_ = nullptr;
    }

    return *this;
}

template <typename T, typename U>
coursework::AvlTree<T, U>::~AvlTree() noexcept
{
    clear(root_);
}

template <typename T, typename U>
typename coursework::AvlTree<T, U>::Iterator coursework::AvlTree<T, U>::begin()
{
    Node* res = root_;

    while (res->left_ != nullptr)
    {
        res = res->left_;
    }

    return Iterator(root_, res);
}

template <typename T, typename U>
typename coursework::AvlTree<T, U>::Iterator coursework::AvlTree<T, U>::end()
{
    return Iterator(root_, nullptr);
}

template <typename T, typename U>
typename coursework::AvlTree<T, U>::ConstIterator coursework::AvlTree<T, U>::begin() const
{
    return begin();
}

template <typename T, typename U>
typename coursework::AvlTree<T, U>::ConstIterator coursework::AvlTree<T, U>::end() const
{
    return end();
}

template <typename T, typename U>
typename coursework::AvlTree<T, U>::ConstIterator coursework::AvlTree<T, U>::cbegin() const
{
    return begin();
}

template <typename T, typename U>
typename coursework::AvlTree<T, U>::ConstIterator coursework::AvlTree<T, U>::cend() const
{
    return end();
}

template <typename T, typename U>
typename coursework::AvlTree<T, U>::Iterator coursework::AvlTree<T, U>::insert(const T& key, U&& value)
{
    if (root_ == nullptr)
    {
        root_ = new Node(key, std::forward<U>(value));
        return begin();
    }

    Node* curr = root_;
    Node* prev = nullptr;

    while (curr != nullptr && key != curr->data_.key_)
    {
        prev = curr;
        curr = key < curr->data_.key_ ? curr->left_ : curr->right_;
    }

    if (curr != nullptr)
    {
        return end();
    }

    curr = new Node(key, std::forward<U>(value), prev);
    (key < curr->parent_->data_.key_ ? curr->parent_->left_ : curr->parent_->right_) = curr;

    return Iterator(root_, curr);
}

template <typename T, typename U>
void coursework::AvlTree<T, U>::clear(Node* rhs)
{
    if (rhs != nullptr)
    {
        clear(rhs->left_);
        clear(rhs->right_);
        delete rhs;
    }
}

#endif // AVL_TREE_HPP
