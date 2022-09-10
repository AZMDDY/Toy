// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_CONTEXT_H
#define TOY_CONTEXT_H
#include <memory>
#include <utility>
#include "Log.h"
#include "IState.h"

class Context : public std::enable_shared_from_this<Context> {
public:
    Context(const IStatePtr& initState) : curState(initState), timeCount(0), stateRefresh(false) {}
    ~Context() = default;

    void SetState(const IStatePtr& state)
    {
        curState = state;
        stateRefresh = true;
    }

    bool IsException() const
    {
        if (!curState) {
            LOG_ERROR() << "curState is nullptr.";
            return true;
        }
        return curState->IsException();
    }

    bool IsEnd() const
    {
        if (!curState) {
            LOG_ERROR() << "curState is nullptr.";
            return true;
        }
        return curState->Type() == STATE_END;
    }

    // 每隔timeInterval ms执行一次Handle
    void Handle(uint32_t timeInterval)
    {
        curState->HandleAction(shared_from_this());
        // HandleAction中可能刷新状态
        if (stateRefresh) {
            stateRefresh = false;
            timeCount = 0;
            // 状态刷新后，立即执行
            curState->HandleAction(shared_from_this());
            return;
        }
        curState->HandleTimeOut(timeCount);
        // HandleTimeOut中可能刷新状态
        if (stateRefresh) {
            stateRefresh = false;
            timeCount = 0;
            // 状态刷新后，立即执行
            curState->HandleAction(shared_from_this());
        }
        timeCount += timeInterval;
    }

private:
    IStatePtr curState;
    uint32_t timeCount;
    bool stateRefresh;
};

#endif  // TOY_CONTEXT_H
