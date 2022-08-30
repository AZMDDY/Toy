// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 类型转换

#ifndef TOY_CONVERT_H
#define TOY_CONVERT_H
#include <string>
#include <type_traits>

namespace Utility {
// 将枚举值转换成底层整型类型
template<typename E>
constexpr auto Enum2Int(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

template<std::size_t N>
inline std::string ToString(const char (&chr)[N])
{
    return {chr, strnlen(chr, N)};
}

inline std::string ToString(const char* chr, size_t len)
{
    return {chr, strnlen(chr, len)};
}

template<typename T>
inline std::string ToString(T value)
{
    return std::to_string(value);
}

}  // namespace Utility
#endif  // TOY_CONVERT_H
