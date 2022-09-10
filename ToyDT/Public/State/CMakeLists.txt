# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description:

message("Compile Public State DT")

include_directories(${TOY_PATH}/Utility/Log)
include_directories(${TOY_PATH}/Utility/Thread)
include_directories(${TOY_PATH}/Public/State)

set(EXEC_NAME dt-public-state)

set(SRCS_LIST StateTest.cpp)

add_executable(${EXEC_NAME} ${SRCS_LIST})

target_link_libraries(${EXEC_NAME}
        gtest
        gtest_main
        pthread)

target_link_libraries(${EXEC_NAME}
        utility_log)