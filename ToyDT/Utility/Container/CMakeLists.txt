# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description:


message("Compile Container DT")

include_directories(${TOY_PATH}/Utility/Log)
include_directories(${TOY_PATH}/Utility/Container)

set(SRCS_LIST BiMapTest.cpp)

add_executable(dt-utility-container ${SRCS_LIST})

target_link_libraries(dt-utility-container
        gtest
        gtest_main
        pthread)

target_link_libraries(dt-utility-container
        utility_log)