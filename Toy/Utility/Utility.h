// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_UTILITY_H
#define TOY_UTILITY_H
#include <cstddef>
namespace Utility {
// 获得C风格数组的大小
template<typename T, std::size_t N>
constexpr std::size_t ArraySize(T (&)[N]) noexcept
{
    return N;
}
}  // namespace Utility
#endif  // TOY_UTILITY_H
