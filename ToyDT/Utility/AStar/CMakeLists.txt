# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description:

message("Compile AStar DT")

include_directories(${TOY_PATH}/Utility/Log)
include_directories(${TOY_PATH}/Utility/AStar)
include_directories(${TOY_PATH}/Utility/Thread)
set(SRCS_LIST AStarTest.cpp)

add_executable(dt-utility-astar ${SRCS_LIST})

target_link_libraries(dt-utility-astar
        gtest
        gtest_main
        pthread)

target_link_libraries(dt-utility-astar
        utility_log utility_astar)