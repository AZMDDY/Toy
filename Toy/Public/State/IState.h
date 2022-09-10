// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_ISTATE_H
#define TOY_ISTATE_H
#include <cstdint>
#include <memory>
#include "Type.h"
class IState;
class Context;

using IStatePtr = std::shared_ptr<IState>;
using ContextPtr = std::shared_ptr<Context>;

// 状态类型：
const uint32_t STATE_END = 0;  // 结束

class IState {
public:
    explicit IState(uint32_t type, uint32_t timeOutLen = 0, uint32_t retryCnt = 0)
        : isFinished(false), ctx(nullptr), stateType(type), timeOut(timeOutLen), timeOutRetryCnt(retryCnt),
          timeOutCnt(0), isException(false), isHandled(false)
    {
    }

    virtual ~IState() = default;

    uint32_t HandleAction(const ContextPtr& context)
    {
        // 已经处理过，则不再处理
        if (isHandled) {
            return EOK;
        }
        if (!context) {
            LOG_ERROR() << "context is nullpter";
            return ERR;
        }
        ctx = context;

        // 保证只Handle一次
        isHandled = true;
        return HandleAction();
    }

    uint32_t HandleTimeOut(uint32_t timeCnt)
    {
        // 完成、异常或者没有配置超时
        if (isFinished || isException || timeOut == 0) {
            return EOK;
        }

        // 已达到超时重试次数
        if (timeOutCnt == timeOutRetryCnt) {
            isException = true;
            return HandleException();
        }

        // 还没到超时时间
        if (timeOutCnt == static_cast<uint32_t>(timeCnt / timeOut)) {
            return EOK;
        }
        timeOutCnt++;
        return HandleTimeOut();
    }

    bool IsFinished() const { return isFinished; }

    bool IsException() const { return isException; }

    uint32_t Type() const { return stateType; }

protected:
    virtual uint32_t HandleAction() = 0;
    virtual uint32_t HandleTimeOut() = 0;
    // 超时重试次数耗尽时，触发异常处理
    virtual uint32_t HandleException() { return EOK; }

protected:
    bool isFinished;
    ContextPtr ctx;
    const uint32_t stateType;        // 状态类型
    const uint32_t timeOut;          // 超时时长 ms
    const uint32_t timeOutRetryCnt;  // 超时重试次数
    uint32_t timeOutCnt;             // (实际)超时次数
private:
    bool isException;  // 是否异常
    bool isHandled;    // 是否已经处理过(执行过HandleAction)
};
#endif  // TOY_ISTATE_H
