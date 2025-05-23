#ifndef AVL_TREE_MAP_HPP
#define AVL_TREE_MAP_HPP

#include <initializer_list>
#include <utility>
#include "AvlTreeMapIterator.hpp"
#include "AvlTreeMapConstIterator.hpp"
#include "AvlTreeMapNode.hpp"
#include "AvlTreeTraverseStrategy.hpp"

namespace coursework
{
    template <typename T, typename U>
    class AvlTreeMap
    {
        using Node = detail::AvlTreeMapNode<T, U>;

    public:

        using Iterator = detail::AvlTreeMapIterator<T, U>;
        using ConstIterator = detail::AvlTreeMapConstIterator<T, U, detail::StraightInfixTraverse<Node>>;
        using ReverseIterator = detail::AvlTreeMapIterator<T, U, detail::ReversedInfixTraverse<Node>>;
        using ConstReverseIterator = detail::AvlTreeMapConstIterator<T, U, detail::ReversedInfixTraverse<Node>>;

        AvlTreeMap();
        AvlTreeMap(const AvlTreeMap& rhs);
        AvlTreeMap(AvlTreeMap&& rhs) noexcept;
        AvlTreeMap(std::initializer_list<std::pair<T, U>> rhs);
        template <typename InputIterator>
        AvlTreeMap(InputIterator begin, InputIterator end);

        AvlTreeMap& operator=(const AvlTreeMap& rhs);
        AvlTreeMap& operator=(AvlTreeMap&& rhs) noexcept;

        virtual ~AvlTreeMap() noexcept;

        Iterator begin();
        Iterator end();
        ConstIterator cbegin() const;
        ConstIterator cend() const;
        ConstIterator begin() const;
        ConstIterator end() const;

        ReverseIterator rbegin();
        ReverseIterator rend();
        ConstReverseIterator crbegin() const;
        ConstReverseIterator crend() const;
        ConstReverseIterator rbegin() const;
        ConstReverseIterator rend() const;

        Iterator insert(T key, U value);
        Iterator search(const T& key) const;
        Iterator remove(const T& key);

        const Node* getRoot() const;

    private:

        void clear(Node* rhs);
        Node* root_;
    };
}

template <typename T, typename U>
coursework::AvlTreeMap<T, U>::AvlTreeMap():
    root_(nullptr)
{}

template <typename T, typename U>
coursework::AvlTreeMap<T, U>::AvlTreeMap(const AvlTreeMap& rhs):
    root_(nullptr)
{
    AvlTreeMap<T, U> temp;

    for (const auto& i : rhs)
    {
        temp.insert(i.first, i.second);
    }

    std::swap(root_, temp.root_);
}

template <typename T, typename U>
coursework::AvlTreeMap<T, U>::AvlTreeMap(std::initializer_list<std::pair<T, U>> rhs)
{
    AvlTreeMap<T, U> temp;

    for (const auto& i : rhs)
    {
        temp.insert(i.first, i.second);
    }

    root_ = temp.root_;
    temp.root_ = nullptr;
}

template <typename T, typename U>
coursework::AvlTreeMap<T, U>& coursework::AvlTreeMap<T, U>::operator=(const AvlTreeMap& rhs)
{
    if (this != &rhs)
    {
        AvlTreeMap<T, U> temp(rhs);
        std::swap(root_, temp.root_);
    }

    return *this;
}

template <typename T, typename U>
coursework::AvlTreeMap<T, U>::AvlTreeMap(AvlTreeMap&& rhs) noexcept:
    root_(rhs.root_)
{
    rhs.root_ = nullptr;
}

template <typename T, typename U>
coursework::AvlTreeMap<T, U>& coursework::AvlTreeMap<T, U>::operator=(AvlTreeMap&& rhs) noexcept
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
coursework::AvlTreeMap<T, U>::~AvlTreeMap() noexcept
{
    clear(root_);
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::Iterator coursework::AvlTreeMap<T, U>::begin()
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

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::Iterator coursework::AvlTreeMap<T, U>::end()
{
    return Iterator(root_, nullptr);
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstIterator coursework::AvlTreeMap<T, U>::cbegin() const
{
    if (root_ == nullptr)
    {
        return cend();
    }

    Node* res = root_;

    while (res->left_ != nullptr)
    {
        res = res->left_;
    }

    return ConstIterator(root_, res);
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstIterator coursework::AvlTreeMap<T, U>::cend() const
{
    return ConstIterator(root_, nullptr);
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstIterator coursework::AvlTreeMap<T, U>::begin() const
{
    return cbegin();
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstIterator coursework::AvlTreeMap<T, U>::end() const
{
    return cend();
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ReverseIterator coursework::AvlTreeMap<T, U>::rbegin()
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

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ReverseIterator coursework::AvlTreeMap<T, U>::rend()
{
    return ReverseIterator(root_, nullptr);
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstReverseIterator coursework::AvlTreeMap<T, U>::crbegin() const
{
    if (root_ == nullptr)
    {
        return crend();
    }

    Node* res = root_;

    while (res->right_ != nullptr)
    {
        res = res->right_;
    }

    return ConstReverseIterator(root_, res);
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstReverseIterator coursework::AvlTreeMap<T, U>::crend() const
{
    return ConstReverseIterator(root_, nullptr);
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstReverseIterator coursework::AvlTreeMap<T, U>::rbegin() const
{
    return rbegin();
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstReverseIterator coursework::AvlTreeMap<T, U>::rend() const
{
    return rend();
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::Iterator coursework::AvlTreeMap<T, U>::insert(T key, U value)
{
    if (root_ == nullptr)
    {
        root_ = new Node(std::move(key), std::move(value));
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

    curr = new Node(std::move(key), std::move(value), prev);
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

    return Iterator(root_, curr);
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::Iterator coursework::AvlTreeMap<T, U>::search(const T& key) const
{
    Node* curr = root_;

    while (curr != nullptr && key != curr->key_)
    {
        curr = key < curr->key_ ? curr->left_ : curr->right_;
    }

    return Iterator(root_, curr);
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::Iterator coursework::AvlTreeMap<T, U>::remove(const T& key)
{
    Node* curr = root_;

    while (curr != nullptr && key != curr->key_)
    {
        curr = key < curr->key_ ? curr->left_ : curr->right_;
    }

    if (curr == nullptr)
    {
        return end();
    }

    Node* res = detail::stepForward(root_, curr);

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
    }
    else if (curr->left_ == nullptr || curr->right_ == nullptr)
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

        bool isRebalanced = false;

        Node* prevBack = currChild;
        Node* currBack = prevBack->parent_;

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
    }
    else
    {
        Node* prev = nullptr;
        Node* const temp = curr;

        curr = curr->right_;

        while (curr->left_ != nullptr)
        {
            prev = curr;
            curr = curr->left_;
        }

        Node* prevBack = temp;

        const bool hasAnyChildren = prev != nullptr;

        (hasAnyChildren ? prev->left_ : temp->right_) = curr->right_;

        if (curr->right_ != nullptr)
        {
            curr->right_->parent_ = hasAnyChildren ? prev : temp;
        }

        *const_cast<T*>(&temp->key_) = std::move(curr->key_);

        bool isRebalanced = false;

        Node* currBack = prevBack->parent_;

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

        res = temp;
    }

    delete curr;
    return Iterator(root_, res);
}

template <typename T, typename U>
const typename coursework::AvlTreeMap<T, U>::Node* coursework::AvlTreeMap<T, U>::getRoot() const
{
    return root_;
}

template <typename T, typename U>
void coursework::AvlTreeMap<T, U>::clear(Node* rhs)
{
    if (rhs != nullptr)
    {
        clear(rhs->left_);
        clear(rhs->right_);
        delete rhs;
    }
}

#endif // AVL_TREE_MAP_HPP
