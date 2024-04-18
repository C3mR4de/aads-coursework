#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <initializer_list>
#include "AvlTreeIterator.hpp"
#include "AvlTreeNode.hpp"

namespace coursework
{
    template <typename T>
    class AvlTree
    {
    public:

        using Iterator = AvlTreeIterator<T>;
        using ConstIterator = AvlTreeIterator<T>;

        AvlTree();
        AvlTree(const AvlTree& rhs) = delete;
        AvlTree(AvlTree&& rhs) noexcept;
        AvlTree(std::initializer_list<T> rhs);
        template <typename InputIterator>
        AvlTree(InputIterator begin, InputIterator end);

        AvlTree& operator=(const AvlTree& rhs) = delete;
        AvlTree& operator=(AvlTree&& rhs) noexcept;

        ~AvlTree() noexcept;

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;
        ConstIterator cbegin() const;
        ConstIterator cend() const;

        Iterator rbegin();
        Iterator rend();
        ConstIterator rbegin() const;
        ConstIterator rend() const;
        ConstIterator crbegin() const;
        ConstIterator crend() const;

        Iterator insert(const T& rhs);

    private:

        void clear(detail::AvlTreeNode<T>* rhs);
        void leftRotate();
        void rightRotate();

        detail::AvlTreeNode<T>* root_;
    };
}

template <typename T>
coursework::AvlTree<T>::AvlTree():
    root_(nullptr)
{}

template <typename T>
coursework::AvlTree<T>::~AvlTree() noexcept
{
    clear(root_);
}

template <typename T>
void coursework::AvlTree<T>::clear(coursework::detail::AvlTreeNode<T>* rhs)
{
    if (rhs != nullptr)
    {
        clear(rhs->left_);
        clear(rhs->right_);
        delete rhs;
    }
}

template <typename T>
typename coursework::AvlTree<T>::Iterator coursework::AvlTree<T>::insert(const T& rhs)
{
    return begin();
}

#endif // AVL_TREE_HPP
