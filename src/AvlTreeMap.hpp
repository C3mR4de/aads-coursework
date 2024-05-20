#ifndef AVL_TREE_MAP_HPP
#define AVL_TREE_MAP_HPP

#include <initializer_list>
#include <utility>
#include "AvlTreeMapIterator.hpp"
#include "AvlTreeMapNode.hpp"
#include "AvlTreeTraverseStrategy.hpp"

namespace coursework
{
    template <typename T, typename U>
    class AvlTreeMap
    {
        using Node = detail::AvlTreeMapNode<T, U>;
        using ConstNode = detail::AvlTreeMapNode<T, const U>;
        using Data = Pair<const T&, U&>;

    public:

        using Iterator = AvlTreeMapIterator<T, U>;
        using ConstIterator = AvlTreeMapIterator<T, const U, detail::StraightInfixTraverse<ConstNode>>;
        using ReverseIterator = AvlTreeMapIterator<T, U, detail::ReversedInfixTraverse<Node>>;
        using ConstReverseIterator = AvlTreeMapIterator<T, const U, detail::ReversedInfixTraverse<Node>>;

        AvlTreeMap();
        AvlTreeMap(const AvlTreeMap&) = delete;
        AvlTreeMap(AvlTreeMap&& rhs) noexcept;
        AvlTreeMap(std::initializer_list<T> rhs);
        template <typename InputIterator>
        AvlTreeMap(InputIterator begin, InputIterator end);

        AvlTreeMap& operator=(const AvlTreeMap&) = delete;
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

        Iterator insert(T&& key, U&& value);
        Iterator search(const T& key) const;
        Iterator remove(const T& key, const T& value);

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
    ConstNode* res = root_;

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
typename coursework::AvlTreeMap<T, U>::Iterator coursework::AvlTreeMap<T, U>::insert(T&& key, U&& value)
{
    if (root_ == nullptr)
    {
        root_ = new Node(std::forward<T>(key), std::forward<U>(value));
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

    curr = new Node(std::forward<T>(key), std::forward<U>(value), prev);
    (curr->key_ < curr->parent_->key_ ? curr->parent_->left_ : curr->parent_->right_) = curr;

    root_ = root_->balance();
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
typename coursework::AvlTreeMap<T, U>::Iterator coursework::AvlTreeMap<T, U>::remove(const T& key, const T& value)
{

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
