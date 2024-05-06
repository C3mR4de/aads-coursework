#ifndef AVL_TREE_NODE_HPP
#define AVL_TREE_NODE_HPP

#include <utility>
#include "Pair.hpp"

namespace coursework
{
    namespace detail
    {
        template <typename T, typename U>
        struct AvlTreeNode
        {
            Pair<const T, U> data_;

            AvlTreeNode* parent_;
            AvlTreeNode* left_;
            AvlTreeNode* right_;

            int factor_;

            AvlTreeNode(const T& key,
                        U&& value,
                        AvlTreeNode* parent = nullptr,
                        AvlTreeNode* left = nullptr,
                        AvlTreeNode* right = nullptr);

            void fixFactor() noexcept;
            AvlTreeNode* rotateLeft() noexcept;
            AvlTreeNode* rotateRight() noexcept;
            AvlTreeNode* balance() noexcept;
        };
    }
}

template<typename T, typename U>
coursework::detail::AvlTreeNode<T, U>::AvlTreeNode(const T& key,
                                                   U&& value,
                                                   AvlTreeNode* parent,
                                                   AvlTreeNode* left,
                                                   AvlTreeNode* right):
    data_(key, std::forward<U>(value)),
    parent_(parent),
    left_(left),
    right_(right),
    factor_(0)
{}

template<typename T, typename U>
void coursework::detail::AvlTreeNode<T, U>::fixFactor() noexcept
{
    int factorLeft = left_ == nullptr ? factor_ - 1 : left_->factor_;
	int factorRight = right_ == nullptr ? factor_ + 1 : right_->factor_;
	factor_ = (factorLeft > factorRight ? factorLeft : factorRight) + 1;
}

template<typename T, typename U>
coursework::detail::AvlTreeNode<T, U>* coursework::detail::AvlTreeNode<T, U>::rotateLeft() noexcept
{
    if (this != nullptr && right_ != nullptr)
    {
        AvlTreeNode<T, U>* p = right_;

        right_ = p->left_;
        p->left_ = this;

        fixFactor();
        p->fixFactor();

        return p;
    }

    return this;
}

template<typename T, typename U>
coursework::detail::AvlTreeNode<T, U>* coursework::detail::AvlTreeNode<T, U>::rotateRight() noexcept
{
    if (this != nullptr && left_ != nullptr)
    {
        AvlTreeNode<T, U>* p = left_;

        left_ = p->right_;
        p->right_ = this;

        fixFactor();
        p->fixFactor();

        return p;
    }

    return this;
}

template<typename T, typename U>
coursework::detail::AvlTreeNode<T, U>* coursework::detail::AvlTreeNode<T, U>::balance() noexcept
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
