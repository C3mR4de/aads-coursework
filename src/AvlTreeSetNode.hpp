#ifndef AVL_TREE_SET_NODE_HPP
#define AVL_TREE_SET_NODE_HPP

#include <utility>

namespace coursework
{
    namespace detail
    {
        template <typename T>
        struct AvlTreeSetNode
        {
            const T key_;

            AvlTreeSetNode* parent_;
            AvlTreeSetNode* left_;
            AvlTreeSetNode* right_;

            int factor_;

            AvlTreeSetNode(T&& key,
                           AvlTreeSetNode* parent = nullptr,
                           AvlTreeSetNode* left = nullptr,
                           AvlTreeSetNode* right = nullptr);

            AvlTreeSetNode<T>* smallLeftRotate(AvlTreeSetNode<T>*& root) noexcept;
            AvlTreeSetNode<T>* smallRightRotate(AvlTreeSetNode<T>*& root) noexcept;
            AvlTreeSetNode<T>* bigLeftRotate(AvlTreeSetNode<T>*& root) noexcept;
            AvlTreeSetNode<T>* bigRightRotate(AvlTreeSetNode<T>*& root) noexcept;
            AvlTreeSetNode<T>* balance(AvlTreeSetNode<T>*& root) noexcept;
        };
    }
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>::AvlTreeSetNode(T&& key,
                                                      AvlTreeSetNode* parent,
                                                      AvlTreeSetNode* left,
                                                      AvlTreeSetNode* right):
    key_(std::move(key)),
    parent_(parent),
    left_(left),
    right_(right),
    factor_(0)
{}

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::smallLeftRotate(AvlTreeSetNode<T>*& root) noexcept
{
    AvlTreeSetNode<T>* pivot = right_;

    if (pivot->factor_ == 1)
    {
        factor_ = 0;
        pivot->factor_ = 0;
    }
    else if (pivot->factor_ == 0)
    {
        factor_ = 1;
        pivot->factor_ = -1;
    }

    right_ = pivot->left_;

    if (pivot->left_ != nullptr)
    {
        pivot->left_->parent_ = this;
    }

    pivot->parent_ = parent_;

    if (parent_ != nullptr)
    {
        (this == parent_->left_ ? parent_->left_ : parent_->right_) = pivot;
    }
    else
    {
        root = pivot;
    }

    pivot->left_ = this;
    parent_ = pivot;

    return pivot;
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::smallRightRotate(AvlTreeSetNode<T>*& root) noexcept
{
    AvlTreeSetNode<T>* pivot = left_;

    if (pivot->factor_ == -1)
    {
        factor_ = 0;
        pivot->factor_ = 0;
    }
    else if (pivot->factor_ == 0)
    {
        factor_ = -1;
        pivot->factor_ = 1;
    }

    left_ = pivot->right_;

    if (pivot->right_ != nullptr)
    {
        pivot->right_->parent_ = this;
    }

    pivot->parent_ = parent_;

    if (parent_ != nullptr)
    {
        (this == parent_->left_ ? parent_->left_ : parent_->right_) = pivot;
    }
    else
    {
        root = pivot;
    }

    pivot->right_ = this;
    parent_ = pivot;

    return pivot;
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::bigLeftRotate(AvlTreeSetNode<T>*& root) noexcept
{
    right_->smallRightRotate(root);
    return smallLeftRotate(root);
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::bigRightRotate(AvlTreeSetNode<T>*& root) noexcept
{
    left_->smallLeftRotate(root);
    return smallRightRotate(root);
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::balance(AvlTreeSetNode<T>*& root) noexcept
{
    if (factor_ == 2)
    {
        if (right_->factor_ < 0)
        {
            return bigLeftRotate(root);
        }
        else
        {
            return smallLeftRotate(root);
        }
    }

    if (factor_ == -2)
    {
        if (left_->factor_ > 0)
        {
            return bigRightRotate(root);
        }
        else
        {
            return smallRightRotate(root);
        }
    }

    return this;
}

#endif // AVL_TREE_SET_NODE_HPP
