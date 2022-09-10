# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description: AStar

message("Compile Utility AStar")

set(SRCS_LIST Pos.cpp Zone.cpp Map.cpp AStar.cpp)

add_library(utility_astar STATIC ${SRCS_LIST})