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
void coursework::DictionaryList<T>::clear()
{
    while (head_ != nullptr)
    {
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
    }
}

#endif // DICTIONARY_LIST_HPP
