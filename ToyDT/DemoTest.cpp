// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "gtest/gtest.h"

class DemoFixtrue : public testing::Test {
public:
    DemoFixtrue() = default;
    ~DemoFixtrue() override = default;

    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}

    void DoSomething() {}

protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(DemoFixtrue, test1)
{
    DoSomething();
}