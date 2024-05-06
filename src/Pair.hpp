#ifndef PAIR_HPP
#define PAIR_HPP

#include <utility>

namespace coursework
{
    template <typename T, typename U>
    struct Pair
    {
        T key_;
        U value_;

        Pair(const T& key, U&& value);
    };
}

template <typename T, typename U>
coursework::Pair<T, U>::Pair(const T& key, U&& value):
    key_(key),
    value_(std::forward<U>(value))
{}

#endif // PAIR_HPP
