// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: os平台定义

#ifndef TOY_PLATFORM_H
#define TOY_PLATFORM_H
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#    define OS_PLATFORM 1
#elif defined(__CYGWIN__) || defined(__CYGWIN32__)
#    define OS_PLATFORM 2
#elif defined(linux) || defined(__linux) || defined(__linux__)
#    define OS_PLATFORM 3
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#    define OS_PLATFORM 4
#elif defined(__FreeBSD__)
#    define OS_PLATFORM 5
#elif defined(__NetBSD__)
#    define OS_PLATFORM 6
#elif defined(__OpenBSD__)
#    define OS_PLATFORM 7
#else
#    define OS_PLATFORM 0
#endif

enum {
    OS_OTHER = 0,
    OS_WINDOWS = 1,
    OS_CYGWIN = 2,
    OS_LINUX = 3,
    OS_MACOSX = 4,
    OS_FREEBSD = 5,
    OS_NETBSD = 6,
    OS_OPENBSD = 7,
    OS_BUTT
};

const char PLATFORM[OS_BUTT][15] = {"OTHER", "WINDOWS", "CYGWIN", "LINUX", "MACOSX", "FREEBSD", "NETBSD", "OS_OPENBSD"};
#endif  // TOY_PLATFORM_H
