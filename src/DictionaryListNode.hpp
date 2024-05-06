#ifndef DICTIONARY_LIST_NODE_HPP
#define DICTIONARY_LIST_NODE_HPP

#include <utility>

namespace coursework
{
    namespace detail
    {
        template <typename T>
        struct DictionaryListNode
        {
            T data_;
            DictionaryListNode* next_;

            DictionaryListNode(T&& rhs, DictionaryListNode* next = nullptr);
        };
    }
}

template <typename T>
coursework::detail::DictionaryListNode<T>::DictionaryListNode(T&& rhs, DictionaryListNode* next):
    data_(std::forward<T>(rhs)),
    next_(next)
{}

#endif // DICTIONARY_LIST_NODE_HPP
