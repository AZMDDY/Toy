// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "Map.h"
namespace Utility {
namespace AStar {
    Map::Map(uint32_t w, uint32_t h) : width(w), height(h), map(w * h)
    {
        for (uint32_t x = 0; x < w; x++) {
            for (uint32_t y = 0; y < h; y++) {
                map[GetVal({x, y})] = Zone({x, y});
            }
        }
    }
}  // namespace AStar
}  // namespace Utility