// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_MAP_H
#define TOY_MAP_H
#include <vector>
#include "Zone.h"
namespace Utility {
namespace AStar {
    class Map {
    public:
        Map(uint32_t w, uint32_t h);
        ~Map() = default;

        bool InRange(const Pos& pos) const { return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height; }

        // 不做范围检查
        Zone& operator[](const Pos& pos) { return map[GetVal(pos)]; }

        const Zone& operator[](const Pos& pos) const { return map[GetVal(pos)]; }

    private:
        uint32_t GetVal(const Pos& pos) const { return pos.y * width + pos.x; }

    private:
        uint32_t width;
        uint32_t height;
        std::vector<Zone> map;
    };
}  // namespace AStar
}  // namespace Utility
#endif  // TOY_MAP_H
