#ifndef DICTIONARY_LIST_ITERATOR_HPP
#define DICTIONARY_LIST_ITERATOR_HPP

#include <iterator>
#include "DictionaryListNode.hpp"

namespace coursework
{
    template <typename T>
    class DictionaryList;

    template <typename T>
    class DictionaryListIterator: std::iterator<std::forward_iterator_tag, const T>
    {
    public:

        friend class DictionaryList<T>;
        using Node = detail::DictionaryListNode<T>;

        DictionaryListIterator();
        DictionaryListIterator(const DictionaryListIterator&) = default;
        ~DictionaryListIterator() = default;

        DictionaryListIterator& operator=(const DictionaryListIterator&) = default;

        DictionaryListIterator& operator++();
        DictionaryListIterator operator++(int);

        T& operator*();
        const T& operator*() const;

        T& operator->();
        const T& operator->() const;

        bool operator==(const DictionaryListIterator& rhs) const;
        bool operator!=(const DictionaryListIterator& rhs) const;

    private:

        Node* head_;
        Node* node_;
        explicit DictionaryListIterator(Node* head, Node* node);
    };
}

template <typename T>
coursework::DictionaryListIterator<T>::DictionaryListIterator():
    head_(nullptr),
    node_(nullptr)
{}
template <typename T>
coursework::DictionaryListIterator<T>::DictionaryListIterator(Node* head, Node* node):
    head_(head),
    node_(node)
{}

template <typename T>
coursework::DictionaryListIterator<T>& coursework::DictionaryListIterator<T>::operator++()
{
    node_ = node_->next_;
    return *this;
}

template <typename T>
coursework::DictionaryListIterator<T> coursework::DictionaryListIterator<T>::operator++(int)
{
    DictionaryListIterator<T> temp(*this);
    ++(*this);
    return temp;
}

template <typename T>
T& coursework::DictionaryListIterator<T>::operator*()
{
    return node_->data_;
}

template <typename T>
const T& coursework::DictionaryListIterator<T>::operator*() const
{
    return node_->data_;
}

template <typename T>
T& coursework::DictionaryListIterator<T>::operator->()
{
    return node_->data_;
}

template <typename T>
const T& coursework::DictionaryListIterator<T>::operator->() const
{
    return node_->data_;
}

template <typename T>
bool coursework::DictionaryListIterator<T>::operator==(const DictionaryListIterator& rhs) const
{
    return head_ == rhs.head_ && node_ == rhs.node_;
}

template <typename T>
bool coursework::DictionaryListIterator<T>::operator!=(const DictionaryListIterator& rhs) const
{
    return !(*this == rhs);
}

#endif // DICTIONARY_LIST_ITERATOR_HPP
