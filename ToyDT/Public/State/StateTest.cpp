// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "gtest/gtest.h"
#include "Type.h"
#include "Thread.h"
#include "FuncTimeCalculator.h"
#include "Context.h"
#include "EndState.h"

using namespace Utility;

class StateTestFixtrue : public testing::Test {
public:
    StateTestFixtrue() = default;
    ~StateTestFixtrue() override = default;

    static void SetUpTestSuite() { SetLogLevel(LogLevel::DEBUG); }
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
    BState() : IState(2, 100, 1) {}
    ~BState() override = default;
};

class AState : public IState {
public:
    AState() : IState(1, 100, 3) {}
    ~AState() override = default;

protected:
    uint32_t HandleAction() override
    {
        LOG_ERROR() << "handle A";
        return EOK;
    }
    uint32_t HandleTimeOut() override
    {
        LOG_ERROR() << "A Retry...";
        if (timeOutCnt == timeOutRetryCnt) {
            ctx->SetState(std::make_shared<BState>());
        }
        return EOK;
    }
};

TEST_F(StateTestFixtrue, StateCreate)
{
    SetLogLevel(LogLevel::ERROR);

    auto ctx = std::make_shared<Context>(std::make_shared<AState>());
    FUNC_TIME_CAL();
    while (true) {
        ctx->Handle(10);
        if (ctx->IsEnd() || ctx->IsException()) {
            return;
        }
        SleepFor(10.0);
    }
}