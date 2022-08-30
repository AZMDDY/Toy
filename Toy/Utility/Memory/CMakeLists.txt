# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description: 内存分配

message("Compile Utility Memory")

set(SRCS_LIST PoolAlloc.cpp)

add_library(utility_memory STATIC ${SRCS_LIST})