#ifndef AVL_TREE_MAP_HPP
#define AVL_TREE_MAP_HPP

#include <initializer_list>
#include <utility>
#include "AvlTreeMapIterator.hpp"
#include "AvlTreeMapNode.hpp"
#include "IteratorStrategy.hpp"

namespace coursework
{
    template <typename T, typename U>
    class AvlTreeMap
    {
        using Node = detail::AvlTreeMapNode<T, U>;
        using Data = Pair<T, U>;

    public:

        using Iterator = AvlTreeMapIterator<T, U>;
        using ConstIterator = AvlTreeMapIterator<T, const U>;
        using ReverseIterator = AvlTreeMapIterator<T, U, detail::ReversedStrategy<detail::AvlTreeMapNode<T, const U>>>;
        using ConstReverseIterator = AvlTreeMapIterator<T, const U, detail::ReversedStrategy<detail::AvlTreeMapNode<T, const U>>>;

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
        ConstIterator begin() const;
        ConstIterator end() const;
        ConstIterator cbegin() const;
        ConstIterator cend() const;

        ReverseIterator rbegin();
        ReverseIterator rend();
        ConstReverseIterator rbegin() const;
        ConstReverseIterator rend() const;
        ConstReverseIterator crbegin() const;
        ConstReverseIterator crend() const;

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
typename coursework::AvlTreeMap<T, U>::ConstIterator coursework::AvlTreeMap<T, U>::begin() const
{
    return begin();
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstIterator coursework::AvlTreeMap<T, U>::end() const
{
    return end();
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstIterator coursework::AvlTreeMap<T, U>::cbegin() const
{
    return begin();
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstIterator coursework::AvlTreeMap<T, U>::cend() const
{
    return end();
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
typename coursework::AvlTreeMap<T, U>::ConstReverseIterator coursework::AvlTreeMap<T, U>::crbegin() const
{
    return rbegin();
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::ConstReverseIterator coursework::AvlTreeMap<T, U>::crend() const
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

    while (curr != nullptr && key != curr->data_.key_)
    {
        prev = curr;
        curr = key < curr->data_.key_ ? curr->left_ : curr->right_;
    }

    if (curr != nullptr)
    {
        return end();
    }

    curr = new Node(std::forward<T>(key), std::forward<U>(value), prev);
    (key < curr->parent_->data_.key_ ? curr->parent_->left_ : curr->parent_->right_) = curr;

    root_ = root_->balance();
    return Iterator(root_, curr);
}

template <typename T, typename U>
typename coursework::AvlTreeMap<T, U>::Iterator coursework::AvlTreeMap<T, U>::search(const T& key) const
{
    Node* curr = root_;

    while (curr != nullptr && key != curr->data_.key_)
    {
        curr = key < curr->data_.key_ ? curr->left_ : curr->right_;
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
