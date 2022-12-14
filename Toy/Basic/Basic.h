// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_BASIC_H
#define TOY_BASIC_H
#include "Patform.h"
#include "Type.h"

// 用于消除unused编译告警
#define UNUSED(x)  \
    do {           \
        (void)(x); \
    } while (0)

template<class T>
struct Range {
    T min;
    T max;
    bool Contain(const T& val) { return val >= min && val <= max; }
};
#endif  // TOY_BASIC_H
