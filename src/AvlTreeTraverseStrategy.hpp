#ifndef AVL_TREE_TRAVERSE_STRATEGY_HPP
#define AVL_TREE_TRAVERSE_STRATEGY_HPP

namespace coursework
{
    namespace detail
    {
        template <typename T>
        T* stepForward(T* root, T* node);

        template <typename T>
        T* stepBackward(T* root, T* node);

        template <typename T>
        struct StraightInfixTraverse
        {
            static T* next(T* root, T* node);
            static T* prev(T* root, T* node);
        };

        template <typename T>
        struct ReversedInfixTraverse
        {
            static T* next(T* root, T* node);
            static T* prev(T* root, T* node);
        };
    }
}

template <typename T>
T* coursework::detail::stepForward(T* root, T* node)
{
    T* curr = node;

    while (curr->right_ == nullptr || curr->key_ < node->key_)
    {
        if (curr == root && (root->right_ == nullptr || curr->key_ < node->key_))
        {
            return nullptr;
        }

        curr = curr->parent_;

        if (curr->key_ > node->key_)
        {
            return curr;
        }
    }

    curr = curr->right_;

    while (curr->left_ != nullptr)
    {
        curr = curr->left_;
    }

    return curr;
}

template <typename T>
T* coursework::detail::stepBackward(T* root, T* node)
{
    T* curr = node;

    while (curr->left_ == nullptr || curr->key_ > node->key_)
    {
        if (curr == root && (root->left_ == nullptr || curr->key_ > node->key_))
        {
            return nullptr;
        }

        curr = curr->parent_;

        if (curr->key_ < node->key_)
        {
            return curr;
        }
    }

    curr = curr->left_;

    while (curr->right_ != nullptr)
    {
        curr = curr->right_;
    }

    return curr;
}

template <typename T>
T* coursework::detail::StraightInfixTraverse<T>::next(T* root, T* node)
{
    return stepForward(root, node);
}

template <typename T>
T* coursework::detail::StraightInfixTraverse<T>::prev(T* root, T* node)
{
    return stepBackward(root, node);
}

template <typename T>
T* coursework::detail::ReversedInfixTraverse<T>::next(T* root, T* node)
{
    return stepBackward(root, node);
}

template <typename T>
T* coursework::detail::ReversedInfixTraverse<T>::prev(T* root, T* node)
{
    return stepForward(root, node);
}

#endif // AVL_TREE_TRAVERSE_STRATEGY_HPP
