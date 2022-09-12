// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:
#include "gtest/gtest.h"
#include "Log.h"
#include "AStar.h"
using namespace Utility::AStar;

class AStarTestFixtrue : public testing::Test {
public:
    AStarTestFixtrue() : myMap(12, 12) {}
    ~AStarTestFixtrue() override = default;

    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}

    void InitMap()
    {
        // 12 x 12
        std::vector<uint32_t> map1 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                                       0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
                                       0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        myMap.Init(map1);
    }

protected:
    void SetUp() override { InitMap(); }
    void TearDown() override {}

protected:
    Map myMap;
    AStar aStar;
};

TEST_F(AStarTestFixtrue, Distance)
{
    Pos pos1(0, 0);
    Pos pos2(1, 10);
    EXPECT_EQ(Distance(pos1, pos1), 0);
    EXPECT_EQ(Distance(pos1, pos2), 10);
    EXPECT_EQ(Distance(pos2, pos1), 10);
}

TEST_F(AStarTestFixtrue, Unit)
{
    EXPECT_EQ(myMap[Pos(1, 1)].HaveUnit(Unit::WALL), 1);
    EXPECT_EQ(myMap[Pos(1, 1)].IsSpace(), false);
}

TEST_F(AStarTestFixtrue, Find)
{
    auto path = aStar.FindPath(myMap, {0, 0}, {11, 11});
    for (auto& pos : path) {
        LOG_ERROR() << pos.ToStr();
    }
    EXPECT_EQ(path.empty(), false);
}

class AStar1 : public AStar {
protected:
    bool PosIsValid(const Map& map, uint32_t step, const Pos& pos) const override
    {
        //        if (step > 10) {
        //            return false;
        //        }
        return AStar::PosIsValid(map, step, pos);
    }
};

TEST_F(AStarTestFixtrue, LimitStep)
{
    AStar1 aStar1;
    EXPECT_EQ(myMap[Pos(4, 4)].IsSpace(), true);

    auto path = aStar1.FindPath(myMap, {0, 0}, {4, 4});
    for (auto& pos : path) {
        LOG_ERROR() << pos.ToStr();
    }
    EXPECT_EQ(path.empty(), false);
}
