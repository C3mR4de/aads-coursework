#ifndef AVL_TREE_SET_NODE_HPP
#define AVL_TREE_SET_NODE_HPP

#include <utility>
#include <algorithm>

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

            // void fixFactor() noexcept;
            AvlTreeSetNode<T>* rotateLeft(AvlTreeSetNode<T>*& root) noexcept;
            AvlTreeSetNode<T>* rotateRight(AvlTreeSetNode<T>*& root) noexcept;
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

// template <typename T>
// void coursework::detail::AvlTreeSetNode<T>::fixFactor() noexcept
// {
//     int factorLeft = left_ == nullptr ? 0 : left_->factor_;
//     int factorRight = right_ == nullptr ? 0 : right_->factor_;
//     factor_ = (factorLeft > factorRight ? factorLeft : factorRight) + 1;
// }

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::rotateLeft(AvlTreeSetNode<T>*& root) noexcept
{
    AvlTreeSetNode<T>* pivot = right_;

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
    factor_ = factor_ + 1 - std::min(pivot->factor_, 0);
    pivot->factor_ = pivot->factor_ + 1 - std::max(factor_, 0);

    return pivot;
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::rotateRight(AvlTreeSetNode<T>*& root) noexcept
{
    AvlTreeSetNode<T>* pivot = left_;

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
    factor_ = factor_ + 1 - std::min(pivot->factor_, 0);
    pivot->factor_ = pivot->factor_ + 1 - std::max(factor_, 0);

    return pivot;
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::balance(AvlTreeSetNode<T>*& root) noexcept
{
    if (factor_ == 2)
    {
        if (right_->factor_ < 0)
        {
            right_ = right_->rotateRight(root);
        }

        return rotateLeft(root);
    }

    if (factor_ == -2)
    {
        if (left_->factor_ > 0)
        {
            left_ = left_->rotateLeft(root);
        }

        return rotateRight(root);
    }

    return this;
}

#endif // AVL_TREE_SET_NODE_HPP
