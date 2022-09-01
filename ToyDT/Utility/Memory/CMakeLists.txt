# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description: Memory DT

message("Compile Memory DT")

include_directories(${TOY_PATH}/Utility/Memory)

set(SRCS_LIST MemoryTest.cpp)

add_executable(dt-utility-memory ${SRCS_LIST})

target_link_libraries(dt-utility-memory
        gtest
        gtest_main
        pthread)

target_link_libraries(dt-utility-memory
        utility_log)