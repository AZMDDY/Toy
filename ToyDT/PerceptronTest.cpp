// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "gtest/gtest.h"
#include "Perceptron.h"

class PerceptronFixtrue : public testing::Test {
public:
    PerceptronFixtrue() = default;
    ~PerceptronFixtrue() override = default;

protected:
    void SetUp() override
    {
        initWeight.fill(0);
        datas[0] = {0, 100, 0};
        datas[1] = {0, 0, 100};
        datas[2] = {0, 100, 100};
    }
    void TearDown() override {}

protected:
    std::array<int32_t, 3> initWeight;
    std::array<std::array<int32_t, 3>, 3> datas;
};

TEST_F(PerceptronFixtrue, test1)
{
    Perceptron<3> perceptron(initWeight);
    int32_t eVal = perceptron.Estimate(datas[0]);
    EXPECT_EQ(eVal, 0);
    perceptron.UpdateWeight(10, 1, 0, datas[0]);
}