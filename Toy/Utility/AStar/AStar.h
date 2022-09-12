// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: A*算法

#ifndef TOY_ASTAR_H
#define TOY_ASTAR_H
#include <set>
#include "Pos.h"
#include "Map.h"
namespace Utility {
namespace AStar {
    class AStar {
    public:
        AStar() = default;
        virtual ~AStar() = default;
        AStar(const AStar& aStar) = delete;
        AStar operator=(const AStar& aStar) = delete;

        std::vector<Pos> FindPath(const Map& map, const Pos& startPos, const Pos& endPos);

    protected:
        virtual bool PosIsValid(const Map& map, uint32_t step, const Pos& pos) const;

        // 起点到当前点的代价
        virtual uint32_t Start2CurCost(const Pos& startPos, const Pos& curPos) const
        {
            return MoveCost(startPos, curPos);
        }

        // 当前点到终点的预估代价
        virtual uint32_t Cur2EndCost(const Pos& curPos, const Pos& endPos) const { return MoveCost(curPos, endPos); }

        // 通用的移动代价
        virtual uint32_t MoveCost(const Pos& pos1, const Pos& pos2) const { return Distance<D8_EQ>(pos1, pos2); }

    private:
        class PosCost;
        using PosCostPtr = std::shared_ptr<PosCost>;
        class PosCost {
        public:
            PosCost() : step(0), cost(0), parent(nullptr), pos(0, 0) {}

            PosCost(const Pos& pos, uint32_t cost, uint32_t step = 0, PosCostPtr parent = nullptr)
                : step(step), cost(cost), parent(std::move(parent)), pos(pos)
            {
            }
            PosCost(const PosCost& cost) = default;
            ~PosCost() = default;

            bool operator<(const PosCost& posCost) const { return this->cost < posCost.cost; }

            const Pos& operator()() const { return pos; }

        public:
            uint32_t step;  // 当前步数
            uint32_t cost;  // 代价
            PosCostPtr parent;

        private:
            Pos pos;
        };

    private:
        void MigratePoint(const Map& map, const PosCost& posCost, const Pos& startPos, const Pos& endPos);

        void OpenZoneEmplace(const PosCost& posCost);
        PosCost OpenZonePop();
        void Clear();

    private:
        std::multiset<PosCost> openZone;  // 待考察的点，按照代价从小到大排序
        std::multiset<Pos> openZoneCopy;  // 用于快速查找点
        std::set<Pos> closeZone;          // 已考察的点
    };
}  // namespace AStar
}  // namespace Utility
#endif  // TOY_ASTAR_H
