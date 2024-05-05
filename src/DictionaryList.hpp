#ifndef DICTIONARY_LIST_HPP
#define DICTIONARY_LIST_HPP

#include <initializer_list>
#include "DictionaryListIterator.hpp"

namespace coursework
{
    template <typename T>
    class DictionaryList
    {
        using Node = detail::DictionaryListNode<T>;

    public:

        using Iterator = DictionaryListIterator<T>;
        using ConstIterator = DictionaryListIterator<const T>;

        DictionaryList();
        DictionaryList(const DictionaryList& rhs) = delete;
        DictionaryList(DictionaryList&& rhs) noexcept;
        DictionaryList(std::initializer_list<T> rhs);
        template <typename InputIterator>
        DictionaryList(InputIterator begin, InputIterator end);

        DictionaryList& operator=(const DictionaryList& rhs) = delete;
        DictionaryList& operator=(DictionaryList&& rhs) noexcept;

        ~DictionaryList() noexcept;

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;
        ConstIterator cbegin() const;
        ConstIterator cend() const;

        Iterator insert(T&& rhs);
        Iterator erase(const T& rhs);
        Iterator search(const T& rhs) const;

    private:

        void clear();
        Node* head_;
    };
}

template <typename T>
coursework::DictionaryList<T>::DictionaryList():
    head_(nullptr)
{}

template <typename T>
coursework::DictionaryList<T>::DictionaryList(DictionaryList&& rhs) noexcept:
    head_(rhs.head_)
{
    rhs.head_ = nullptr;
}

template <typename T>
coursework::DictionaryList<T>& coursework::DictionaryList<T>::operator=(DictionaryList&& rhs) noexcept
{
    if (this != &rhs)
    {
        clear();
        head_ = rhs.head_;
        rhs.head_ = nullptr;
    }

    return *this;
}

template <typename T>
coursework::DictionaryList<T>::~DictionaryList<T>() noexcept
{
    clear();
}

template <typename T>
typename coursework::DictionaryList<T>::Iterator coursework::DictionaryList<T>::begin()
{
    return Iterator(head_, head_);
}


template <typename T>
typename coursework::DictionaryList<T>::Iterator coursework::DictionaryList<T>::end()
{
    return Iterator(head_, nullptr);
}

template <typename T>
typename coursework::DictionaryList<T>::ConstIterator coursework::DictionaryList<T>::begin() const
{
    return begin();
}


template <typename T>
typename coursework::DictionaryList<T>::ConstIterator coursework::DictionaryList<T>::end() const
{
    return end();
}

template <typename T>
typename coursework::DictionaryList<T>::ConstIterator coursework::DictionaryList<T>::cbegin() const
{
    return begin();
}


template <typename T>
typename coursework::DictionaryList<T>::ConstIterator coursework::DictionaryList<T>::cend() const
{
    return end();
}

template <typename T>
typename coursework::DictionaryList<T>::Iterator coursework::DictionaryList<T>::insert(T&& rhs)
{
    if (head_ == nullptr)
    {
        head_ = new Node(std::forward<T>(rhs));
        return begin();
    }

    if (rhs < head_->data_)
    {
        Node* newNode = new Node(std::forward<T>(rhs));
        newNode->next_ = head_;
        head_ = newNode;

        return Iterator(head_, newNode);
    }

    Node* curr = head_;

    while (curr->next_ != nullptr && curr->next_->data_ < rhs)
    {
        curr = curr->next_;
    }

    if (curr->next_ != nullptr && curr->next_->data_ == rhs)
    {
        return end();
    }

    if (curr->data_ < rhs)
    {
        Node* newNode = new Node(std::forward<T>(rhs));
        newNode->next_ = curr->next_;
        curr->next_ = newNode;

        return Iterator(head_, newNode);
    }

    return end();
}

template <typename T>
typename coursework::DictionaryList<T>::Iterator coursework::DictionaryList<T>::erase(const T& rhs)
{
    if (head_ == nullptr)
    {
        return end();
    }

    if (rhs == head_->data_)
    {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;

        return begin();
    }

    Node* curr = head_;

    while (curr->next_ != nullptr && curr->next_->data_ != rhs)
    {
        curr = curr->next_;
    }

    if (curr->next_ == nullptr)
    {
        return end();
    }

    Node* temp = curr->next_;
    curr->next_ = curr->next_->next_;
    delete temp;

    return Iterator(head_, curr);
}

template <typename T>
typename coursework::DictionaryList<T>::Iterator coursework::DictionaryList<T>::search(const T& rhs) const
{
    Node* curr = head_;

    while (curr != nullptr && curr->data_ != rhs)
    {
        curr = curr->next_;
    }

    return Iterator(head_, curr);
}

template <typename T>
void coursework::DictionaryList<T>::clear()
{
    while (head_ != nullptr)
    {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
    }
}

#endif // DICTIONARY_LIST_HPP
