#ifndef AVL_TREE_NODE_HPP
#define AVL_TREE_NODE_HPP

#include <utility>
#include "Pair.hpp"

namespace coursework
{
    namespace detail
    {
        template <typename T, typename U>
        struct AvlTreeMapNode
        {
            Pair<const T, U> data_;

            AvlTreeMapNode* parent_;
            AvlTreeMapNode* left_;
            AvlTreeMapNode* right_;

            int factor_;

            AvlTreeMapNode(const T&& key,
                           U&& value,
                           AvlTreeMapNode* parent = nullptr,
                           AvlTreeMapNode* left = nullptr,
                           AvlTreeMapNode* right = nullptr);

            void fixFactor() noexcept;
            AvlTreeMapNode* rotateLeft() noexcept;
            AvlTreeMapNode* rotateRight() noexcept;
            AvlTreeMapNode* balance() noexcept;
        };
    }
}

template<typename T, typename U>
coursework::detail::AvlTreeMapNode<T, U>::AvlTreeMapNode(const T&& key,
                                                         U&& value,
                                                         AvlTreeMapNode* parent,
                                                         AvlTreeMapNode* left,
                                                         AvlTreeMapNode* right):
    data_(std::forward<const T>(key), std::forward<U>(value)),
    parent_(parent),
    left_(left),
    right_(right),
    factor_(0)
{}

template<typename T, typename U>
void coursework::detail::AvlTreeMapNode<T, U>::fixFactor() noexcept
{
    int factorLeft = left_ == nullptr ? factor_ - 1 : left_->factor_;
	int factorRight = right_ == nullptr ? factor_ + 1 : right_->factor_;
	factor_ = (factorLeft > factorRight ? factorLeft : factorRight) + 1;
}

template<typename T, typename U>
coursework::detail::AvlTreeMapNode<T, U>* coursework::detail::AvlTreeMapNode<T, U>::rotateLeft() noexcept
{
    if (this != nullptr && right_ != nullptr)
    {
        AvlTreeMapNode<T, U>* pivot = right_;

        right_ = pivot->left_;
        pivot->left_ = this;

        fixFactor();
        pivot->fixFactor();

        return pivot;
    }

    return this;
}

template<typename T, typename U>
coursework::detail::AvlTreeMapNode<T, U>* coursework::detail::AvlTreeMapNode<T, U>::rotateRight() noexcept
{
    if (this != nullptr && left_ != nullptr)
    {
        AvlTreeMapNode<T, U>* pivot = left_;

        left_ = pivot->right_;
        pivot->right_ = this;

        fixFactor();
        pivot->fixFactor();

        return pivot;
    }

    return this;
}

template<typename T, typename U>
coursework::detail::AvlTreeMapNode<T, U>* coursework::detail::AvlTreeMapNode<T, U>::balance() noexcept
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

#endif // AVL_TREE_NODE_HPP
