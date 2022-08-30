# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description: 读写操作文件

message("Compile Utility RwxFile")

set(SRCS_LIST RwxFile.cpp)

add_library(utility_rwx_file STATIC ${SRCS_LIST})