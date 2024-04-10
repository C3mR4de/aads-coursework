#ifndef AVL_TREE_CONST_ITERATOR_HPP
#define AVL_TREE_CONST_ITERATOR_HPP

#include "AvlTreeNode.hpp"
#include <iterator>

namespace coursework
{
    template <typename T>
    class AvlTree;

    template <typename T>
    class AvlTreeConstIterator: std::iterator<std::bidirectional_iterator_tag, T>
    {
        friend class AvlTree<T>;

    public:

        AvlTreeConstIterator();
        AvlTreeConstIterator(const AvlTreeConstIterator&) = default;
        ~AvlTreeConstIterator() = default;

        AvlTreeConstIterator& operator=(const AvlTreeConstIterator&) = default;
        AvlTreeConstIterator& operator++();
        AvlTreeConstIterator& operator++(int);
        AvlTreeConstIterator& operator--();
        AvlTreeConstIterator& operator--(int);

        const T& operator*() const;
        const T& operator->() const;

        bool operator==(const AvlTreeConstIterator& other);
        bool operator!=(const AvlTreeConstIterator& other);

    private:

        const Node<T>* node_;
        explicit AvlTreeConstIterator(Node<T>* node);
    };
}

#endif // AVL_TREE_CONST_ITERATOR_HPP

