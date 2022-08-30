// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_SOCKETDEFINE_H
#define TOY_SOCKETDEFINE_H
#include <cstdint>
namespace Utility {
const uint32_t IPV4_BIN_MAX_LEN = 4;   // 二进制ipv4的长度4Bytes
const uint32_t IPV6_BIN_MAX_LEN = 16;  // 二进制ipv6的长度16Bytes
const uint32_t IPV4_STR_MAX_LEN = 15;  // 字符串ipv4的长度15Bytes(不包含'\0'). "xxx.xxx.xxx.xxx"
const uint32_t IPV6_STR_MAX_LEN = 39;  // 字符串ipv6的长度39Bytes(不包含'\0'). "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx"
const uint32_t IPV4_BIN_INT32_MAX_LEN = 1;  // 二进制ipv4的长度：1 int32
const uint32_t IPV6_BIN_INT32_MAX_LEN = 4;  // 二进制ipv6的长度：4 int32

// Internet 协议版本
enum class IpType : uint8_t {
    IPV4 = 2,  // AF_INET
    IPV6 = 10  // AF_INET6
};

}  // namespace Utility
#endif  // TOY_SOCKETDEFINE_H
