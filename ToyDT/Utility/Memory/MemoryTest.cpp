// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 内存接口测试

#include "gtest/gtest.h"
#include "PoolAlloc.h"
using namespace Utility;

class MemoryTestFixtrue : public testing::Test {
public:
    MemoryTestFixtrue() = default;
    ~MemoryTestFixtrue() override = default;

    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}

protected:
    void SetUp() override {}
    void TearDown() override {}

protected:
    PoolAlloc<> poolAlloc;
};

/*
 * 测试内容：测试内存池初始化
 * 预期结果：初始化成功
 *
 * */
TEST_F(MemoryTestFixtrue, PollAllocInitCase)
{
    EXPECT_EQ(poolAlloc.Init(), EOK);
}

/*
 * 测试内容：测试内存池重复初始化
 * 预期结果：重复初始化不成功
 *
 * */
TEST_F(MemoryTestFixtrue, PollAllocReInitCase)
{
    EXPECT_EQ(poolAlloc.Init(), EOK);
    EXPECT_EQ(poolAlloc.Init(), ERR);
}

/*
 * 测试内容：测试内存池分配小于最大分配内存单元的内存
 * 预期结果：分配内存成功
 *
 * */
TEST_F(MemoryTestFixtrue, PollAllocMemLessMaxUintCase)
{
    EXPECT_EQ(poolAlloc.Init(), EOK);
    void* ptr = poolAlloc.Alloc(7);
    EXPECT_EQ(poolAlloc.Size() - poolAlloc.RemainSize(), 8);
}

/*
 * 测试内容：测试内存池优先分配free list中的内存
 * 预期结果：优先分配free list中的内存
 *
 * */
TEST_F(MemoryTestFixtrue, PollAllocMemInFreeListCase)
{
    EXPECT_EQ(poolAlloc.Init(), EOK);
    void* ptr = poolAlloc.Alloc(13);
    EXPECT_EQ(poolAlloc.Size() - poolAlloc.RemainSize(), 16);
    auto ptr1 = ptr;
    poolAlloc.Free(ptr, 16);
    EXPECT_EQ(ptr, nullptr);

    ptr = poolAlloc.Alloc(15);
    EXPECT_EQ(poolAlloc.Size() - poolAlloc.RemainSize(), 16);
    auto ptr2 = ptr;
    EXPECT_EQ(ptr1, ptr2);
    poolAlloc.Free(ptr, 16);
}