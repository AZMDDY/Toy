// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_SOCKETADDR_H
#define TOY_SOCKETADDR_H
#include "SocketDefine.h"
#include "Log.h"
namespace Utility {
struct SocketAddr {
    IpType type;
    union {
        uint32_t ipv4;                          // ipv4地址：1个4字节
        uint32_t ipv6[IPV6_BIN_INT32_MAX_LEN];  // ipv6地址：4个4字节
        uint8_t v4[IPV4_BIN_MAX_LEN];
        uint8_t v6[IPV6_BIN_MAX_LEN];
    } u;
    uint16_t port;

    SocketAddr() : type(IpType::IPV4), u(), port(0) {}

    bool operator==(const SocketAddr& addr) const
    {
        if (!(type == addr.type && port == addr.port)) {
            return false;
        }
        if (type == IpType::IPV4) {
            return u.ipv4 == addr.u.ipv4;
        }
        if (type == IpType::IPV6) {
            for (int i = 0; i < IPV6_BIN_INT32_MAX_LEN; i++) {
                if (u.ipv6[i] != addr.u.ipv6[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool operator!=(const SocketAddr& addr) const { return !(*this == addr); }

    bool operator<(const SocketAddr& addr) const
    {
        if (type != addr.type) {
            LOG_ERROR() << "ip version is inconsistent.";
            return type < addr.type;
        }
        if (type == IpType::IPV4) {
            return u.ipv4 < addr.u.ipv4 || port < addr.port;
        }
        if (type == IpType::IPV6) {
            int ret = memcmp(u.v6, addr.u.v6, IPV6_BIN_INT32_MAX_LEN);
            if (ret == 0) {
                return port < addr.port;
            }
            return ret < 0;
        }
        LOG_ERROR() << "invalid ip version: " << type;
        return true;
    }
};
}  // namespace Utility
#endif  // TOY_SOCKETADDR_H
