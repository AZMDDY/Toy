// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 双向Map功能测试

#include "gtest/gtest.h"
#include "Log.h"
#include "BiMap.h"
using namespace Utility;
class BiMapTestFixture : public testing::Test {
public:
    BiMapTestFixture() = default;
    ~BiMapTestFixture() override = default;

    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}

protected:
    void SetUp() override
    {
        EXPECT_EQ(diffMap.Insert(11, 'e'), true);
        EXPECT_EQ(diffMap.Insert(12, 'f'), true);
        EXPECT_EQ(diffMap.Insert(13, 'g'), true);
        EXPECT_EQ(diffMap.Insert(14, 'h'), true);

        EXPECT_EQ(sameMap.Insert(6, 12), true);
        EXPECT_EQ(sameMap.Insert(112, 7), true);
        EXPECT_EQ(sameMap.Insert(13, 67), true);
        EXPECT_EQ(sameMap.Insert(12, 0), true);
    }
    void TearDown() override { diffMap.Clear(); }

protected:
    BiMap<int32_t, char> diffMap;
    BiMap<int32_t, int32_t> sameMap;
};

/*
 * 测试内容：测试BiMap的插入功能
 * 预期结果：插入功能正常
 *
 * */
TEST_F(BiMapTestFixture, InsertTest)
{
    // 插入一个不存在的键值对
    EXPECT_EQ(diffMap.Insert(1, 'a'), true);
    EXPECT_EQ(diffMap.At<L>(1), 'a');
    EXPECT_EQ(diffMap.At<R>('a'), 1);

    // 插入重复的left
    EXPECT_EQ(diffMap.Insert(1, 'b'), false);
    EXPECT_EQ(diffMap.Find<R>('b'), diffMap.CEnd<R>());
    EXPECT_EQ(diffMap.At<L>(1), 'a');

    // 插入重复的right
    EXPECT_EQ(diffMap.Insert(2, 'a'), false);
    EXPECT_EQ(diffMap.Find<L>(2), diffMap.CEnd<L>());
    EXPECT_EQ(diffMap.At<L>(1), 'a');

    // 强制插入相同的left，原键值对应该都删除
    diffMap.InsertF(1, 'b');
    EXPECT_EQ(diffMap.Find<R>('a'), diffMap.CEnd<R>());
    EXPECT_EQ(diffMap.At<L>(1), 'b');

    // 强制插入相同的right，原键值对应该都删除
    diffMap.InsertF(2, 'b');
    EXPECT_EQ(diffMap.Find<L>(1), diffMap.CEnd<L>());
    EXPECT_EQ(diffMap.At<L>(2), 'b');

    // 插入一个不存在的键值对
    EXPECT_EQ(sameMap.Insert(1, 'a'), true);
    EXPECT_EQ(sameMap.At<L>(1), 'a');
    EXPECT_EQ(sameMap.At<R>('a'), 1);

    // 插入重复的left
    EXPECT_EQ(sameMap.Insert(1, 'b'), false);
    EXPECT_EQ(sameMap.Find<R>('b'), sameMap.CEnd<R>());
    EXPECT_EQ(sameMap.At<L>(1), 'a');

    // 插入重复的right
    EXPECT_EQ(sameMap.Insert(2, 'a'), false);
    EXPECT_EQ(sameMap.Find<L>(2), sameMap.CEnd<L>());
    EXPECT_EQ(sameMap.At<L>(1), 'a');

    // 强制插入相同的left，原键值对应该都删除
    sameMap.InsertF(1, 'b');
    EXPECT_EQ(sameMap.Find<R>('a'), sameMap.CEnd<R>());
    EXPECT_EQ(sameMap.At<L>(1), 'b');

    // 强制插入相同的right，原键值对应该都删除
    sameMap.InsertF(2, 'b');
    EXPECT_EQ(sameMap.Find<L>(1), sameMap.CEnd<L>());
    EXPECT_EQ(sameMap.At<L>(2), 'b');
}

/*
 * 测试内容：测试BiMap的删除功能
 * 预期结果：删除功能正常
 *
 * */
TEST_F(BiMapTestFixture, EraseTest)
{
    EXPECT_EQ(diffMap.Insert(1, 'a'), true);
    EXPECT_EQ(diffMap.Insert(2, 'b'), true);
    EXPECT_EQ(diffMap.Insert(3, 'c'), true);
    EXPECT_EQ(diffMap.Insert(4, 'd'), true);
    diffMap.Erase<L>(1);
    EXPECT_EQ(diffMap.Find<R>('a'), diffMap.End<R>());
    diffMap.Erase<R>('b');
    EXPECT_EQ(diffMap.Find<L>(2), diffMap.End<L>());
    EXPECT_EQ(diffMap.Size(), 6);
}

/*
 * 测试内容：测试BiMap的At功能
 * 预期结果：At功能正常
 *
 * */
TEST_F(BiMapTestFixture, AtTest)
{
    EXPECT_EQ(diffMap.At<L>(11), 'e');
    EXPECT_EQ(diffMap.At<R>('f'), 12);
}

/*
 * 测试内容：测试BiMap的迭代器功能
 * 预期结果：迭代器正常
 *
 * */
TEST_F(BiMapTestFixture, IterTest)
{
    for (auto iter = diffMap.Begin<L>(); iter != diffMap.End<L>(); ++iter) {
        LOG_ERROR() << iter->first << ", " << iter->second;
    }

    for (auto iter = diffMap.RBegin<L>(); iter != diffMap.REnd<L>(); ++iter) {
        LOG_ERROR() << iter->first << ", " << iter->second;
    }

    for (auto iter = diffMap.Begin<R>(); iter != diffMap.End<R>(); ++iter) {
        LOG_ERROR() << iter->first << ", " << iter->second;
    }

    for (auto iter = diffMap.RBegin<R>(); iter != diffMap.REnd<R>(); ++iter) {
        LOG_ERROR() << iter->first << ", " << iter->second;
    }

    for (auto iter = sameMap.Begin<L>(); iter != sameMap.End<L>(); ++iter) {
        LOG_ERROR() << iter->first << ", " << iter->second;
    }

    for (auto iter = sameMap.RBegin<L>(); iter != sameMap.REnd<L>(); ++iter) {
        LOG_ERROR() << iter->first << ", " << iter->second;
    }

    for (auto iter = sameMap.Begin<R>(); iter != sameMap.End<R>(); ++iter) {
        LOG_ERROR() << iter->first << ", " << iter->second;
    }

    for (auto iter = sameMap.RBegin<R>(); iter != sameMap.REnd<R>(); ++iter) {
        LOG_ERROR() << iter->first << ", " << iter->second;
    }
}

/*
 * 测试内容：测试BiMap的清除功能
 * 预期结果：正常清除
 *
 * */
TEST_F(BiMapTestFixture, ClearTest)
{
    diffMap.Clear();
    EXPECT_EQ(diffMap.Size(), 0);
    EXPECT_EQ(diffMap.Empty(), true);
}