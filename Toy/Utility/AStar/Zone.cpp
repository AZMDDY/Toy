// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "Zone.h"
namespace Utility {
namespace AStar {
    uint32_t Zone::HaveUnit(const Unit& unit) const { return static_cast<uint32_t>(units.count(unit)); }

    void Zone::AddUnit(const Unit& unit, uint32_t num)
    {
        if (unit == Unit::SPACE) {
            units[Unit::SPACE] = 1;
            return;
        }
        if (unit != Unit::SPACE) {
            units[Unit::SPACE] = 0;
        }
        units[unit] += num;
    }
    void Zone::DelUnit(const Unit& unit, uint32_t num)
    {
        if (units.find(unit) == units.end()) {
            return;
        }

        if (units[unit] <= num) {
            units.erase(unit);
        }

        if ((units.size() == 1 && units.count(Unit::SPACE) != 0) || units.empty()) {
            units[Unit::SPACE] = 1;
        }
    }
    void Zone::DelAllUnit()
    {
        units.clear();
        units[Unit::SPACE] = 1;
    }

    bool Zone::IsSpace() const { return units.count(Unit::SPACE) == 1; }

}  // namespace AStar
}  // namespace Utility