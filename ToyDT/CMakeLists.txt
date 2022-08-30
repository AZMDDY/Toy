# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description:

include_directories(${TOY_PATH}/Basic)
include_directories(${TOY_PATH})
include_directories(${TOY_PATH}/Utility)
include_directories(${TOY_PATH}/Utility/Log)
include_directories(${THIRDPARTY_INC_PATH})

link_directories(${THIRDPARTY_LIB_PATH})

message("Compile ToyDT")

add_subdirectory(Utility)

set(SRCS_LIST DemoTest.cpp PerceptronTest.cpp)

add_executable(dt-toy ${SRCS_LIST})

target_link_libraries(dt-toy
        gtest
        gtest_main
        pthread)