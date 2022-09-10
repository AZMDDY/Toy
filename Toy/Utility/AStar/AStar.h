// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#ifndef TOY_ASTAR_H
#define TOY_ASTAR_H
#include <set>
#include <map>
#include "Pos.h"
#include "Map.h"
namespace Utility {
namespace AStar {
    class AStar {
    public:
        static AStar& Intance();
        AStar(const AStar& aStar) = delete;
        AStar operator=(const AStar& aStar) = delete;

        uint32_t FindPath(const Map& map, const Pos& startPos, const Pos& endPos, std::vector<Pos>& path);

    protected:
        virtual bool PosIsValid(const Map& map, int32_t step, const Pos& pos) const;

        // 起点到当前点的代价
        virtual int32_t StartMoveCost(const Pos& startPos, const Pos& curPos) const;

        // 当前点到终点的预估代价
        virtual int32_t EndMoveCost(const Pos& curPos, const Pos& endPos) const;

        // 通用的移动代价
        virtual int32_t MoveCost(const Pos& pos1, const Pos& pos2) const;

    private:
        AStar() = default;
        ~AStar() = default;

    private:
        class PosCost;
        using PosCostPtr = std::shared_ptr<PosCost>;
        class PosCost {
        public:
            PosCost() : pos(0, 0), cost(0), parent(nullptr) {}

            PosCost(const Pos& pos, int32_t cost, PosCostPtr parent = nullptr)
                : pos(pos), cost(cost), parent(std::move(parent))
            {
            }
            PosCost(const PosCost& cost) = default;
            ~PosCost() = default;

            bool operator<(const PosCost& posCost) const { return this->cost < posCost.cost; }

        public:
            Pos pos;
            int32_t cost;
            PosCostPtr parent;
        };

    private:
        void MigratePoint(const Map& map, const PosCost& posCost, int32_t step, const Pos& startPos, const Pos& endPos);

        void OpenZoneEmplace(const PosCost& posCost);
        PosCost OpenZoneTop() const;
        void OpenZonePop();

    private:
        std::map<PosCost, int32_t> openZone;  // 按照代价从小到大排序
        std::set<Pos> openZoneCopy;           // 用于快速查找
        std::map<Pos, int32_t> closeZone;
    };
}  // namespace AStar
}  // namespace Utility
#endif  // TOY_ASTAR_H
