#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <initializer_list>
#include "AvlTreeIterator.hpp"
#include "AvlTreeNode.hpp"

namespace coursework
{
    template <typename T>
    class AvlTree
    {
    public:

        using Iterator = AvlTreeIterator<T>;
        using ConstIterator = AvlTreeIterator<const T>;

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

        Iterator insert(const T& rhs);

    private:

        void clear(detail::AvlTreeNode<T>* rhs);
        void leftRotate();
        void rightRotate();

        detail::AvlTreeNode<T>* root_;
    };
}

template <typename T>
coursework::AvlTree<T>::AvlTree():
    root_(nullptr)
{}

template <typename T>
coursework::AvlTree<T>::~AvlTree() noexcept
{
    clear(root_);
}

template <typename T>
typename coursework::AvlTree<T>::Iterator coursework::AvlTree<T>::begin()
{
    detail::AvlTreeNode<T>* res = root_;

    while (res->left_ != nullptr)
    {
        res = res->left_;
    }

    return Iterator(root_, res);
}

template <typename T>
typename coursework::AvlTree<T>::Iterator coursework::AvlTree<T>::end()
{
    return Iterator(root_, nullptr);
}

template <typename T>
typename coursework::AvlTree<T>::Iterator coursework::AvlTree<T>::insert(const T& rhs)
{
    using namespace detail;
    using Node = AvlTreeNode<T>;

    if (root_ == nullptr)
    {
        root_ = new Node(rhs);
        return Iterator(root_, root_);
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

    curr = new Node(rhs, prev);
    (rhs < curr->parent_->key_ ? curr->parent_->left_ : curr->parent_->right_) = curr;

    return Iterator(root_, curr);
}

template <typename T>
void coursework::AvlTree<T>::clear(coursework::detail::AvlTreeNode<T>* rhs)
{
    if (rhs != nullptr)
    {
        clear(rhs->left_);
        clear(rhs->right_);
        delete rhs;
    }
}

#endif // AVL_TREE_HPP
