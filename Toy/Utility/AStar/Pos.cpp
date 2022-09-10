// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description:

#include "Pos.h"
#include <sstream>
namespace Utility {
namespace AStar {
    using namespace std;
    Pos operator+(const Pos& aPos, const Pos& bPos) { return {aPos.x + bPos.x, aPos.y + bPos.y}; }

    std::string Pos::ToStr() const
    {
        stringstream ss;
        ss << "(" << x << "," << y << ")";
        return ss.str();
    }
}  // namespace AStar
}  // namespace Utility