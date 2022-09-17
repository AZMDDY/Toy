// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_IMSG_H
#define TOY_IMSG_H
#include <memory>
struct IMsg {
public:
    IMsg() = default;
    virtual ~IMsg() = default;
};
using IMsgPtr = std::shared_ptr<IMsg>;
#endif  // TOY_IMSG_H
