// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 地图中一个点区域，区域为空，指当前是空地

#ifndef TOY_ZONE_H
#define TOY_ZONE_H
#include <unordered_map>
#include "Pos.h"
namespace Utility {
namespace AStar {
    enum class Unit {
        // 0: 空地
        WALL = 1,  // 墙
        BUTT
    };

    class Zone {
    public:
        explicit Zone(const Pos& pos = {0, 0}) : pos(pos) {}
        ~Zone() = default;

        bool operator==(const Zone& zone) const { return pos == zone.pos && units == zone.units; }
        bool operator!=(const Zone& zone) const { return !(*this == zone); }

        uint32_t HaveUnit(const Unit& unit) const;
        void AddUnit(const Unit& unit, uint32_t num = 1);
        void DelUnit(const Unit& unit, uint32_t num = 1);
        void DelAllUnit();
        bool IsSpace() const;
        const Pos& operator()() const { return pos; }

    private:
        Pos pos;
        std::unordered_map<Unit, uint32_t> units;  // size == 0 就表示空地
    };
}  // namespace AStar
}  // namespace Utility
#endif  // TOY_ZONE_H
