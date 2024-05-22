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

            void fixFactor() noexcept;
            AvlTreeSetNode* rotateLeft() noexcept;
            AvlTreeSetNode* rotateRight() noexcept;
            AvlTreeSetNode* balance() noexcept;
        };
    }
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>::AvlTreeSetNode(T&& key,
                                                      AvlTreeSetNode* parent,
                                                      AvlTreeSetNode* left,
                                                      AvlTreeSetNode* right):
    key_(std::forward<T>(key)),
    parent_(parent),
    left_(left),
    right_(right),
    factor_(0)
{}

template <typename T>
void coursework::detail::AvlTreeSetNode<T>::fixFactor() noexcept
{
    int factorLeft = left_ == nullptr ? factor_ - 1 : left_->factor_;
    int factorRight = right_ == nullptr ? factor_ + 1 : right_->factor_;
    factor_ = (factorLeft > factorRight ? factorLeft : factorRight) + 1;
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::rotateLeft() noexcept
{
    if (this != nullptr && right_ != nullptr)
    {
        AvlTreeSetNode<T>* pivot = right_;

        right_ = pivot->left_;
        pivot->left_ = this;

        fixFactor();
        pivot->fixFactor();

        return pivot;
    }

    return this;
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::rotateRight() noexcept
{
    if (this != nullptr && left_ != nullptr)
    {
        AvlTreeSetNode<T>* pivot = left_;

        left_ = pivot->right_;
        pivot->right_ = this;

        fixFactor();
        pivot->fixFactor();

        return pivot;
    }

    return this;
}

template <typename T>
coursework::detail::AvlTreeSetNode<T>* coursework::detail::AvlTreeSetNode<T>::balance() noexcept
{
    fixFactor();

    if (factor_ == 2)
    {
        if (right_ == nullptr ? factor_ + 1 : right_->factor_ < 0)
        {
            right_ = right_->rotateRight();
        }

        return rotateLeft();
    }

    if (factor_ == -2)
    {
        if (left_ == nullptr ? factor_ - 1 : left_->factor_ > 0)
        {
            left_ = left_->rotateLeft();
        }

        return rotateRight();
    }

    return this;
}

#endif // AVL_TREE_SET_NODE_HPP
