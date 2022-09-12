// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: A*算法

#include "AStar.h"
#include <cmath>
#include "Basic.h"
#include "Log.h"
namespace Utility {
namespace AStar {
    std::vector<Pos> AStar::FindPath(const Map& map, const Pos& start, const Pos& target)
    {
        Clear();

        std::vector<Pos> path;
        if (!map.InRange(start) || !map.InRange(target)) {
            LOG_ERROR() << start.ToStr() << " or " << target.ToStr() << "is invalid";
            return path;
        }
        if (start == target) {
            LOG_DEBUG() << "startPos is equal to endPos. " << start.ToStr();
            return path;
        }

        OpenZoneEmplace({start, 0, 0, nullptr});
        while (!openZone.empty()) {
            // 从待考察点集中取出代价最低的点
            auto cheapPos = OpenZonePop();
            // 找到目标点，则回溯获得路径
            if (cheapPos() == target) {
                path.push_back(cheapPos());
                // 回溯
                auto parentPosCost = cheapPos.parent;
                while (parentPosCost) {
                    path.push_back((*parentPosCost)());
                    parentPosCost = parentPosCost->parent;
                }
                break;
            } else {
                // 纳入已考察的点集中
                closeZone.insert(cheapPos());
                // 将cheapPos附近的点加入到待考察点集中
                MigratePoint(map, cheapPos, start, target);
            }
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    bool AStar::PosIsValid(const Map& map, uint32_t step, const Pos& pos) const
    {
        UNUSED(step);
        Zone zone;
        if (!map.InRange(pos)) {
            return false;
        }
        return map[pos].IsSpace();
    }

    void AStar::MigratePoint(const Map& map, const PosCost& posCost, const Pos& startPos, const Pos& endPos)
    {
        // up, down, left, right, diagonal up right, diagonal down right, diagonal down left, diagonal up left
        static int move[8][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}};
        for (auto & i : move) {
            // 下一个位置
            auto nextPos = posCost() + Pos(i[0], i[1]);
            if (!PosIsValid(map, posCost.step + 1, nextPos)) {
                continue;
            }

            if (closeZone.find(nextPos) != closeZone.end()) {
                continue;
            }

            if (openZoneCopy.find(nextPos) != openZoneCopy.end()) {
                continue;
            }
            // 计算点的代价
            uint32_t cost = posCost.cost + Start2CurCost(startPos, nextPos) + Cur2EndCost(nextPos, endPos);
            // 加入到待考察点集中
            OpenZoneEmplace({nextPos, cost, posCost.step + 1, std::make_shared<PosCost>(posCost)});
        }
    }

    void AStar::OpenZoneEmplace(const PosCost& posCost)
    {
        openZone.emplace(posCost);
        openZoneCopy.emplace(posCost());
    }

    AStar::PosCost AStar::OpenZonePop()
    {
        auto iter = openZone.begin();
        PosCost posCost = *iter;

        openZoneCopy.erase((*iter)());
        openZone.erase(iter);
        return posCost;
    }

    void AStar::Clear()
    {
        openZone.clear();
        openZoneCopy.clear();
        closeZone.clear();
    }
}  // namespace AStar
}  // namespace Utility