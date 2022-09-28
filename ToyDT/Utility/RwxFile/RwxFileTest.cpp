// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "gtest/gtest.h"
#include "RwxFile.h"

using namespace Utility;

class RwxFileFixtrue : public testing::Test {
public:
    RwxFileFixtrue() = default;
    ~RwxFileFixtrue() override = default;

    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}

protected:
    void SetUp() override {}
    void TearDown() override {}
};
#pragma pack(1)
struct A {
    int a;       // 4
    double b;    // 8
    char c[10];  // 10
};
#pragma pack()

struct B {
    uint32_t num;
    A data[0];
};

TEST_F(RwxFileFixtrue, RwBinFileTest)
{
    A a{1, 10.2, "1223"};
    auto ret = WriteFile("test.txt", &a);
    EXPECT_EQ(ret, EOK);
    A b;
    ret = ReadFile("test.txt", &b);
    EXPECT_EQ(ret, EOK);
    EXPECT_EQ(b.a, a.a);
    EXPECT_EQ(b.b, a.b);
    LOG_ERROR() << "sizeof(A) = " << sizeof(A);
    std::string aC = a.c;
    std::string bC = b.c;
    EXPECT_EQ(aC, bC);
}

TEST_F(RwxFileFixtrue, RwDataLenTest)
{
    A a{1, 10.2, "1223"};
    uint32_t dataLen = sizeof(B) + sizeof(A) * 2;
    B* c = reinterpret_cast<B*>(malloc(dataLen));
    LOG_ERROR() << "dataLen: " << dataLen;
    c->num = 2;
    c->data[0] = a;
    c->data[1].a = 100;
    c->data[1].b = 6.6666;
    c->data[1].c[2] = 'C';
    auto ret = WriteFile("test.txt", c, dataLen);
    EXPECT_EQ(ret, EOK);

    B* tmpB = static_cast<B*>(malloc(sizeof(B)));
    ret = ReadFile("test.txt", tmpB);
    EXPECT_EQ(ret, EOK);
    EXPECT_EQ(tmpB->num, c->num);
    uint32_t rData = sizeof(B) + sizeof(A) * tmpB->num;
    EXPECT_EQ(rData, dataLen);
    B* d = reinterpret_cast<B*>(malloc(rData));
    ret = ReadFile("test.txt", d, rData);
    EXPECT_EQ(ret, EOK);
    EXPECT_EQ(d->num, c->num);
    EXPECT_EQ(d->data[0].a, c->data[0].a);
    EXPECT_EQ(d->data[0].b, c->data[0].b);
    EXPECT_EQ(d->data[0].c[2], c->data[0].c[2]);
    EXPECT_EQ(d->data[1].a, c->data[1].a);
    EXPECT_EQ(d->data[1].b, c->data[1].b);
    EXPECT_EQ(d->data[1].c[2], c->data[1].c[2]);
    free(tmpB);
    free(d);
    free(c);
}