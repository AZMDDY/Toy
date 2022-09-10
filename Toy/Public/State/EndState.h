// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_ENDSTATE_H
#define TOY_ENDSTATE_H
#include "IState.h"
class EndState : public IState {
public:
    EndState() : IState(STATE_END) {}
    ~EndState() override = default;

protected:
    uint32_t HandleAction() override
    {
        isFinished = true;
        return EOK;
    }
    uint32_t HandleTimeOut() override { return EOK; };
};
#endif  // TOY_ENDSTATE_H
