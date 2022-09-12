// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "Zone.h"
#include "Log.h"
namespace Utility {
namespace AStar {
    uint32_t Zone::HaveUnit(const Unit& unit) const { return static_cast<uint32_t>(units.count(unit)); }

    void Zone::AddUnit(const Unit& unit, uint32_t num) { units[unit] += num; }

    void Zone::DelUnit(const Unit& unit, uint32_t num)
    {
        if (units.find(unit) == units.end()) {
            LOG_ERROR() << "can't find " << unit;
            return;
        }

        if (units[unit] <= num) {
            units.erase(unit);
        }
        LOG_ERROR() << "the unit " << unit << " size: " << units[unit] << ", del num: " << num;
    }

    void Zone::DelAllUnit() { units.clear(); }

    bool Zone::IsSpace() const { return units.empty(); }

}  // namespace AStar
}  // namespace Utility