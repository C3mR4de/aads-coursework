#ifndef AVL_TREE_ITERATOR_HPP
#define AVL_TREE_ITERATOR_HPP

#include "AvlTreeNode.hpp"
#include <iterator>

namespace coursework
{
    template <typename T>
    class AvlTree;

    template <typename T>
    class AvlTreeIterator: std::iterator<std::bidirectional_iterator_tag, T>
    {
        friend class AvlTree<T>;

    public:

        AvlTreeIterator();
        AvlTreeIterator(const AvlTreeIterator&) = default;
        ~AvlTreeIterator() = default;

        AvlTreeIterator& operator=(const AvlTreeIterator&) = default;
        AvlTreeIterator& operator++();
        AvlTreeIterator& operator++(int);
        AvlTreeIterator& operator--();
        AvlTreeIterator& operator--(int);

        T& operator*();
        const T& operator*() const;

        T& operator->();
        const T& operator->() const;

        bool operator==(const AvlTreeIterator& other);
        bool operator!=(const AvlTreeIterator& other);

    private:

        Node<T>* node_;
        explicit AvlTreeIterator(Node<T>* node);
    };
}

#endif // AVL_TREE_ITERATOR_HPP
