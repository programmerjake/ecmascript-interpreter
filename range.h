#ifndef RANGE_H_INCLUDED
#define RANGE_H_INCLUDED

#include <tuple>
#include <utility>
#include <initializer_list>

template <typename T>
class range
{
    T beginV, endV;
public:
    constexpr range()
    {
    }
    constexpr range(T beginV, T endV)
        : beginV(std::move(beginV)), endV(std::move(endV))
    {
    }
    typedef T iterator;
    constexpr const iterator & begin() const
    {
        return beginV;
    }
    constexpr const iterator & end() const
    {
        return endV;
    }
    constexpr const iterator & cbegin() const
    {
        return beginV;
    }
    constexpr const iterator & cend() const
    {
        return endV;
    }
    template <typename U>
    constexpr operator range<U>() const
    {
        return range<U>((U)beginV, (U)endV);
    }
};

template <typename T>
inline constexpr range<T> make_range(T begin, T end)
{
    return range<T>(std::move(begin), std::move(end));
}

template <typename T>
inline constexpr auto make_range(T v) -> range<decltype(begin(v))>
{
    return range<decltype(begin(T()))>(begin(v), end(v));
}

template <typename T, size_t n>
inline constexpr range<T *> make_range(T (&v)[n])
{
    return range<T *>(v, v + n);
}

#endif // RANGE_H_INCLUDED
