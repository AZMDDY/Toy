# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description: RwxFile DT

message("Compile RwxFile DT")

include_directories(${TOY_PATH}/Utility/RwxFile)

set(SRCS_LIST RwxFileTest.cpp)

add_executable(dt-utility-rwxfile ${SRCS_LIST})

target_link_libraries(dt-utility-rwxfile
        gtest
        gtest_main
        pthread)

target_link_libraries(dt-utility-rwxfile
        utility_log utility_rwx_file)