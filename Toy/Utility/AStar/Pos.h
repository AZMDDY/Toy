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
            if (x < pos.x) {
                return true;
            }
            return y < pos.y;
        }

        std::string ToStr() const;

    public:
        uint32_t x;
        uint32_t y;
    };
    Pos operator+(const Pos& aPos, const Pos& bPos);
}  // namespace AStar
}  // namespace Utility
#endif  // TOY_POS_H
