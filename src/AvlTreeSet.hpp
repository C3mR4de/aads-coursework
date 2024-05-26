#ifndef AVL_TREE_SET_HPP
#define AVL_TREE_SET_HPP

#include <initializer_list>
#include <utility>
#include "AvlTreeSetIterator.hpp"
#include "AvlTreeSetNode.hpp"
#include "AvlTreeTraverseStrategy.hpp"

namespace coursework
{
    template <typename T>
    class AvlTreeSet
    {
        using Node = detail::AvlTreeSetNode<T>;

    public:

        using Iterator = AvlTreeSetIterator<T>;
        using ConstIterator = Iterator;
        using ReverseIterator = AvlTreeSetIterator<T, detail::ReversedInfixTraverse<detail::AvlTreeSetNode<T>>>;
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

        Iterator begin() const;
        Iterator end() const;
        ConstIterator cbegin() const;
        ConstIterator cend() const;

        ReverseIterator rbegin() const;
        ReverseIterator rend() const;
        ConstReverseIterator crbegin() const;
        ConstReverseIterator crend() const;

        Iterator insert(T rhs);
        Iterator search(const T& rhs) const;
        Iterator remove(const T& rhs);

        const Node* getRoot() const;

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
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::begin() const
{
    if (root_ == nullptr)
    {
        return end();
    }

    Node* res = root_;

    while (res->left_ != nullptr)
    {
        res = res->left_;
    }

    return Iterator(root_, res);
}

template <typename T>
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::end() const
{
    return Iterator(root_, nullptr);
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
typename coursework::AvlTreeSet<T>::ReverseIterator coursework::AvlTreeSet<T>::rbegin() const
{
    if (root_ == nullptr)
    {
        return rend();
    }

    Node* res = root_;

    while (res->right_ != nullptr)
    {
        res = res->right_;
    }

    return ReverseIterator(root_, res);
}

template <typename T>
typename coursework::AvlTreeSet<T>::ReverseIterator coursework::AvlTreeSet<T>::rend() const
{
    return ReverseIterator(root_, nullptr);
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
typename coursework::AvlTreeSet<T>::Iterator coursework::AvlTreeSet<T>::insert(T rhs)
{
    if (root_ == nullptr)
    {
        root_ = new Node(std::move(rhs));
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

    curr = new Node(std::move(rhs), prev);
    (curr->key_ < curr->parent_->key_ ? curr->parent_->left_ : curr->parent_->right_) = curr;

    bool isRebalanced = false;

    Node* prevBack = curr;
    Node* currBack = prev;

    while (currBack != nullptr && !isRebalanced)
    {
        if (prevBack == currBack->left_)
        {
            --currBack->factor_;
        }
        else if (prevBack == currBack->right_)
        {
            ++currBack->factor_;
        }

        currBack = currBack->balance(root_);

        isRebalanced = currBack->factor_ == 0;

        prevBack = currBack;
        currBack = currBack->parent_;
    }

    /*
    for (Node* i = curr; i->parent_ != nullptr && !isRebalanced; i = i->parent_)
    {
        if (i == i->parent_->left_)
        {
            --(i->parent_->factor_);
        }
        else if (i == i->parent_->right_)
        {
            ++(i->parent_->factor_);
        }

        i->parent_ = i->parent_->balance(root_);
        isRebalanced = i->parent_->factor_ == 0;
    }
    */

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
    Node* curr = root_;

    while (curr != nullptr && rhs != curr->key_)
    {
        curr = rhs < curr->key_ ? curr->left_ : curr->right_;
    }

    if (curr == nullptr)
    {
        return end();
    }

    if (curr->left_ == nullptr && curr->right_ == nullptr)
    {
        if (curr != root_)
        {
            (curr == curr->parent_->left_ ? curr->parent_->left_ : curr->parent_->right_) = nullptr;
        }
        else
        {
            root_ = nullptr;
        }

        Node* res = curr->parent_;
        delete curr;
        return Iterator(root_, res);
    }

    if (curr->left_ == nullptr || curr->right_ == nullptr)
    {
        Node* const currChild = curr->left_ != nullptr ? curr->left_ : curr->right_;

        if (curr == root_)
        {
            currChild->parent_ = nullptr;
            root_ = currChild;
        }
        else
        {
            currChild->parent_ = curr->parent_;
            (curr == curr->parent_->left_ ? curr->parent_->left_ : curr->parent_->right_) = currChild;
        }

        delete curr;

        bool isRebalanced = false;

        Node* prevBack = currChild;
        Node* currBack = currChild->parent_;

        while (currBack != nullptr && !isRebalanced)
        {
            if (prevBack == currBack->left_)
            {
                ++currBack->factor_;
            }
            else if (prevBack == currBack->right_)
            {
                --currBack->factor_;
            }

            currBack = currBack->balance(root_);

            isRebalanced = std::abs(currBack->factor_) == 1;

            prevBack = currBack;
            currBack = currBack->parent_;
        }

        /*
        bool isRebalanced = false;

        for (Node* i = currChild; i->parent_ != nullptr && !isRebalanced; i = i->parent_)
        {
            if (i == i->parent_->left_)
            {
                ++(i->parent_->factor_);
            }
            else if (i == i->parent_->right_)
            {
                --(i->parent_->factor_);
            }

            i->parent_ = i->parent_->balance(root_);
            isRebalanced = std::abs(i->parent_->factor_) == 1;
        }
        */

        return Iterator(root_, currChild);
    }
    else
    {
        /*
        Node* temp = curr;

        temp = temp->right_;

        while (temp->left_ != nullptr)
        {
            temp = temp->left_;
        }

        if (temp->right_ == nullptr)
        {
            temp->parent_->left_ = nullptr;
        }
        else
        {
            temp->parent_->left_ = temp->right_;
            temp->right_->parent_ = temp->parent_;
        }

        temp->parent_ = curr->parent_;

        if (curr != root_)
        {
            (curr == curr->parent_->left_ ? curr->parent_->left_ : curr->parent_->right_) = temp;
        }

        temp->left_ = curr->left_;
        curr->left_->parent_ = temp;

        temp->right_ = curr->right_;
        curr->right_->parent_ = temp;
        */

        Node* prev = nullptr;
        Node* const temp = curr;

        curr = curr->right_;

        while (curr->left_ != nullptr)
        {
            prev = curr;
            curr = curr->left_;
        }

        const bool hasAnyChildren = prev != nullptr;

        (hasAnyChildren ? prev->left_ : temp->right_) = curr->right_;

        if (curr->right_ != nullptr)
        {
            curr->right_->parent_ = hasAnyChildren ? prev : temp;
        }

        *const_cast<T*>(&temp->key_) = std::move(curr->key_);

        bool isRebalanced = false;

        Node* prevBack = temp;
        Node* currBack = temp->parent_;

        while (currBack != nullptr && !isRebalanced)
        {
            if (prevBack == currBack->left_)
            {
                ++currBack->factor_;
            }
            else if (prevBack == currBack->right_)
            {
                --currBack->factor_;
            }

            currBack = currBack->balance(root_);

            isRebalanced = std::abs(currBack->factor_) == 1;

            prevBack = currBack;
            currBack = currBack->parent_;
        }

        /*
        bool isRebalanced = false;

        for (Node* i = temp; i->parent_ != nullptr && !isRebalanced; i = i->parent_)
        {
            if (i == i->parent_->left_)
            {
                ++(i->parent_->factor_);
            }
            else if (i == i->parent_->right_)
            {
                --(i->parent_->factor_);
            }

            i->parent_ = i->parent_->balance(root_);

            if (i == i->parent_)
            {
                i->parent_ = nullptr;
            }

            isRebalanced = std::abs(i->parent_->factor_) == 1;
        }
        */

        return Iterator(root_, temp);
    }

    // delete curr;
    //
    // if (root_ != nullptr)
    // {
    //     bool isRebalanced = false;
    //
    //     for (Node* i = curr; i->parent_ != nullptr && !isRebalanced; i = i->parent_)
    //     {
    //         if (i == i->parent_->left_)
    //         {
    //             --(i->parent_->factor_);
    //         }
    //         else if (i == i->parent_->right_)
    //         {
    //             ++(i->parent_->factor_);
    //         }
    //
    //         i->parent_ = i->parent_->balance(root_);
    //         isRebalanced = i->parent_->factor_ == 0;
    //     }
    // }
}

template <typename T>
const typename coursework::AvlTreeSet<T>::Node* coursework::AvlTreeSet<T>::getRoot() const
{
    return root_;
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
