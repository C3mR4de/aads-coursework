#ifndef AVL_TREE_MAP_NODE_HPP
#define AVL_TREE_MAP_NODE_HPP

#include <utility>

namespace coursework
{
    namespace detail
    {
        template <typename T, typename U>
        struct AvlTreeMapNode
        {
            const T key_;
            U value_;

            std::pair<const T&, U&> data_ = {key_, value_};
            std::pair<const T&, const U&> constData_ = {key_, value_};

            AvlTreeMapNode* parent_;
            AvlTreeMapNode* left_;
            AvlTreeMapNode* right_;

            int factor_;

            AvlTreeMapNode(T&& key,
                           U&& value,
                           AvlTreeMapNode* parent = nullptr,
                           AvlTreeMapNode* left = nullptr,
                           AvlTreeMapNode* right = nullptr);

            AvlTreeMapNode* rotateLeft(AvlTreeMapNode*& root) noexcept;
            AvlTreeMapNode* rotateRight(AvlTreeMapNode*& root) noexcept;
            AvlTreeMapNode* balance(AvlTreeMapNode*& root) noexcept;
        };
    }
}

template <typename T, typename U>
coursework::detail::AvlTreeMapNode<T, U>::AvlTreeMapNode(T&& key,
                                                         U&& value,
                                                         AvlTreeMapNode* parent,
                                                         AvlTreeMapNode* left,
                                                         AvlTreeMapNode* right):
    key_(std::move(key)),
    value_(std::move(value)),
    parent_(parent),
    left_(left),
    right_(right),
    factor_(0)
{}

template <typename T, typename U>
coursework::detail::AvlTreeMapNode<T, U>* coursework::detail::AvlTreeMapNode<T, U>::rotateLeft(AvlTreeMapNode*& root) noexcept
{
    AvlTreeMapNode<T, U>* pivot = right_;

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

template <typename T, typename U>
coursework::detail::AvlTreeMapNode<T, U>* coursework::detail::AvlTreeMapNode<T, U>::rotateRight(AvlTreeMapNode*& root) noexcept
{
    AvlTreeMapNode<T, U>* pivot = left_;

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

template <typename T, typename U>
coursework::detail::AvlTreeMapNode<T, U>* coursework::detail::AvlTreeMapNode<T, U>::balance(AvlTreeMapNode*& root) noexcept
{
    if (factor_ == 2)
    {
        if (right_->factor_ < 0)
        {
            right_->rotateRight(root);
        }

        return rotateLeft(root);
    }

    if (factor_ == -2)
    {
        if (left_->factor_ > 0)
        {
            left_->rotateLeft(root);
        }

        return rotateRight(root);
    }

    return this;
}

#endif // AVL_TREE_MAP_NODE_HPP
