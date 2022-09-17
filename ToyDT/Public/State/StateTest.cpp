// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "gtest/gtest.h"
#include "Type.h"
#include "Thread.h"
#include "FuncTimeCalculator.h"
#include "Context.h"
#include "EndState.h"
#include "IMsg.h"
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

struct TMsg : public IMsg {
public:
    explicit TMsg(int a1): a(a1) {}
    ~TMsg() override = default;
    int a;
};

class BState : public IState {
protected:
    uint32_t HandleAction(IMsgPtr msg) override
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
    BState(const IMsgPtr& iMsg = nullptr) : IState(2, 100, 1,iMsg) {}
    ~BState() override = default;
};

class AState : public IState {
public:
    AState(const IMsgPtr& iMsg = nullptr) : IState(1, 100, 3, iMsg) {}
    ~AState() override = default;

protected:
    uint32_t HandleAction(IMsgPtr msg) override
    {
        LOG_ERROR() << "handle A";
        auto tMsg = std::static_pointer_cast<TMsg>(msg) ;
        EXPECT_EQ(tMsg->a, 10);
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
    auto msg = std::make_shared<TMsg>(10);
    auto ctx = std::make_shared<Context>(std::make_shared<AState>(msg));
    FUNC_TIME_CAL();
    while (true) {
        ctx->Handle(10);
        if (ctx->IsEnd() || ctx->IsException()) {
            return;
        }
        SleepFor(10.0);
    }
}