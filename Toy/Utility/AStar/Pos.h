// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_POS_H
#define TOY_POS_H
#include <cstdint>
#include <string>
namespace Utility {
namespace AStar {
    class Pos {
    public:
        Pos(uint32_t x, uint32_t y) : x(x), y(y) {}
        Pos(const Pos&) = default;
        ~Pos() = default;

        bool operator==(const Pos& pos) const { return x == pos.x && y == pos.y; }
        bool operator!=(const Pos& pos) const { return !(*this == pos); }
        Pos& operator+=(const Pos& pos)
        {
            this->x += pos.x;
            this->y += pos.y;
            return *this;
        }

        bool operator<(const Pos& pos) const
        {
            if (x == pos.x) {
                return y < pos.y;
            }
            return x < pos.x;
        }

        inline uint32_t ToUnit(uint32_t width) const { return y * width + x; }

        std::string ToStr() const;

    public:
        uint32_t x;
        uint32_t y;
    };
    Pos operator+(const Pos& aPos, const Pos& bPos);

    enum DistanceType {
        D8_EQ  // 8个方向移动一格的距离相同
    };

    template<DistanceType type = D8_EQ>
    uint32_t Distance(const Pos& sPos, const Pos& ePos)
    {
        uint32_t dx = std::abs(static_cast<int32_t>(sPos.x - ePos.x));
        uint32_t dy = std::abs(static_cast<int32_t>(sPos.y - ePos.y));
        return dx > dy ? dx : dy;
    }
}  // namespace AStar
}  // namespace Utility
#endif  // TOY_POS_H
