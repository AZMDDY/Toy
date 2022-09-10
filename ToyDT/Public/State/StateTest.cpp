// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "gtest/gtest.h"
#include <thread>
#include "Type.h"
#include "Context.h"
#include "EndState.h"
class StateTestFixtrue : public testing::Test {
public:
    StateTestFixtrue() = default;
    ~StateTestFixtrue() override = default;

    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}

protected:
    void SetUp() override {}
    void TearDown() override {}
};

class BState : public IState {
protected:
    uint32_t HandleAction() override
    {
        LOG_ERROR() << "handle B";
        return EOK;
    }
    uint32_t HandleTimeOut() override
    {
        LOG_ERROR() << "B Retry ...";
        if (timeOutCnt == timeOutRetryCnt) {
            ctx->SetState(std::make_shared<EndState>());
            isFinished = true;
        }
        return EOK;
    }

public:
    BState() : IState(2, 1000, 1) {}
    ~BState() override = default;
};

class AState : public IState {
public:
    AState() : IState(1, 10, 3) {}
    ~AState() override = default;

protected:
    uint32_t HandleAction() override
    {
        LOG_ERROR() << "handle A";
        return EOK;
    }
    uint32_t HandleTimeOut() override
    {
        if (timeOutCnt == timeOutRetryCnt) {
            ctx->SetState(std::make_shared<BState>());
            return EOK;
        }
        LOG_ERROR() << "A Retry...";
        return EOK;
    }
};

TEST_F(StateTestFixtrue, StateCreate)
{
    auto ctx = std::make_shared<Context>(std::make_shared<AState>());
    while (!ctx->IsEnd() && !ctx->IsException()) {
        ctx->Handle(10);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}