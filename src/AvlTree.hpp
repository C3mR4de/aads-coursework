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
        AvlTree(const AvlTree& other) = delete;
        AvlTree(AvlTree&& other) noexcept;
        AvlTree(std::initializer_list<T> init);
        template <typename InputIterator>
        AvlTree(InputIterator begin, InputIterator end);

        AvlTree& operator=(const AvlTree& other) = delete;
        AvlTree& operator=(AvlTree&& other) noexcept;

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

    private:

        void clear(detail::AvlTreeNode<T>* node);
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
void coursework::AvlTree<T>::clear(coursework::detail::AvlTreeNode<T>* node)
{
    if (node != nullptr)
    {
        clear(node->left_);
        clear(node->right_);
    }
}

#endif // AVL_TREE_HPP
