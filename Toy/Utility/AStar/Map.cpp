// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "Map.h"
#include "Type.h"
#include "Log.h"
namespace Utility {
namespace AStar {
    Map::Map(uint32_t w, uint32_t h) : width(w), height(h), map(w * h)
    {
        for (uint32_t x = 0; x < w; x++) {
            for (uint32_t y = 0; y < h; y++) {
                map[Pos2Uint({x, y})] = Zone({x, y});
            }
        }
    }

    uint32_t Map::Init(const std::vector<uint32_t>& data)
    {
        if (data.size() != width * height) {
            LOG_ERROR() << "data size: " << data.size();
            return ERR;
        }
        for (uint32_t i = 0; i < map.size(); i++) {
            if (data[i] == 0) {
                continue;
            }
            map[i].AddUnit(static_cast<Unit>(data[i]));
        }
        return EOK;
    }

}  // namespace AStar
}  // namespace Utility