// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 将两个小类型的数合并成一个大类型的数
// eg. 两个uint8_t合并成一个uint16_t
// smallVal1: 0x01, smallVal2: 0x02; TwoInOne(smallVal1, smallVal2) => BigVal = 0x0102

#ifndef TOY_TWOINONE_H
#define TOY_TWOINONE_H
namespace Utility {
template<typename SmallType, typename BigType>
class TwoInOne {
public:
    TwoInOne() = delete;
    TwoInOne(SmallType smallVal1, SmallType smallVal2) : t2(0)
    {
        // 为了符合阅读习惯 smallVal1smallVal2 == BigVal
        t1[1] = smallVal1;
        t1[0] = smallVal2;
    }
    ~TwoInOne() = default;
    TwoInOne(const TwoInOne<SmallType, BigType>&) = default;

    BigType GetBig() { return t2; }
    SmallType GetSmall1() { return t1[1]; }
    SmallType GetSmall2() { return t1[0]; }

private:
    union {
        SmallType t1[2];
        BigType t2;
    };
};
}  // namespace Utility
#endif  // TOY_TWOINONE_H
