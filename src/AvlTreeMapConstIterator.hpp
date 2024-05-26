#ifndef AVL_TREE_MAP_CONST_ITERATOR_HPP
#define AVL_TREE_MAP_CONST_ITERATOR_HPP

#include <iterator>
#include <utility>
#include "AvlTreeMapNode.hpp"
#include "AvlTreeTraverseStrategy.hpp"

namespace coursework
{
    template <typename T, typename U>
    class AvlTreeMap;

    namespace detail
    {
        template <typename T, typename U, typename S = StraightInfixTraverse<AvlTreeMapNode<T, U>>>
        class AvlTreeMapConstIterator: std::iterator<std::bidirectional_iterator_tag, const T>
        {
            friend class AvlTreeMap<T, U>;
            using Node = AvlTreeMapNode<T, U>;
            using Data = std::pair<const T&, const U&>;

        public:

            AvlTreeMapConstIterator();
            AvlTreeMapConstIterator(const AvlTreeMapConstIterator&) = default;
            ~AvlTreeMapConstIterator() = default;

            AvlTreeMapConstIterator& operator=(const AvlTreeMapConstIterator&) = default;

            AvlTreeMapConstIterator& operator++();
            AvlTreeMapConstIterator operator++(int);
            AvlTreeMapConstIterator& operator--();
            AvlTreeMapConstIterator operator--(int);

            const Data& operator*() const;
            const Data* operator->() const;

            bool operator==(const AvlTreeMapConstIterator& rhs) const;
            bool operator!=(const AvlTreeMapConstIterator& rhs) const;

        private:

            Node* root_;
            Node* node_;
            explicit AvlTreeMapConstIterator(Node* root, Node* node);
        };
    }
}

template <typename T, typename U, typename S>
coursework::detail::AvlTreeMapConstIterator<T, U, S>::AvlTreeMapConstIterator():
    root_(nullptr),
    node_(nullptr)
{}

template <typename T, typename U, typename S>
coursework::detail::AvlTreeMapConstIterator<T, U, S>::AvlTreeMapConstIterator(Node* root, Node* node):
    root_(root),
    node_(node)
{}

template <typename T, typename U, typename S>
coursework::detail::AvlTreeMapConstIterator<T, U, S>& coursework::detail::AvlTreeMapConstIterator<T, U, S>::operator++()
{
    node_ = S::next(root_, node_);
    return *this;
}

template <typename T, typename U, typename S>
coursework::detail::AvlTreeMapConstIterator<T, U, S> coursework::detail::AvlTreeMapConstIterator<T, U, S>::operator++(int)
{
    AvlTreeMapConstIterator<T, U, S> temp(*this);
    ++(*this);
    return temp;
}

template <typename T, typename U, typename S>
coursework::detail::AvlTreeMapConstIterator<T, U, S>& coursework::detail::AvlTreeMapConstIterator<T, U, S>::operator--()
{
    node_ = S::prev(root_, node_);
    return *this;
}

template <typename T, typename U, typename S>
coursework::detail::AvlTreeMapConstIterator<T, U, S> coursework::detail::AvlTreeMapConstIterator<T, U, S>::operator--(int)
{
    AvlTreeMapConstIterator<T, U, S> temp(*this);
    --(*this);
    return temp;
}

template <typename T, typename U, typename S>
const typename coursework::detail::AvlTreeMapConstIterator<T, U, S>::Data& coursework::detail::AvlTreeMapConstIterator<T, U, S>::operator*() const
{
    return node_->constData_;
}

template <typename T, typename U, typename S>
const typename coursework::detail::AvlTreeMapConstIterator<T, U, S>::Data* coursework::detail::AvlTreeMapConstIterator<T, U, S>::operator->() const
{
    return &node_->constData_;
}

template <typename T, typename U, typename S>
bool coursework::detail::AvlTreeMapConstIterator<T, U, S>::operator==(const AvlTreeMapConstIterator& rhs) const
{
    return root_ == rhs.root_ && node_ == rhs.node_;
}

template <typename T, typename U, typename S>
bool coursework::detail::AvlTreeMapConstIterator<T, U, S>::operator!=(const AvlTreeMapConstIterator& rhs) const
{
    return !(*this == rhs);
}

#endif // AVL_TREE_MAP_CONST_ITERATOR_HPP
