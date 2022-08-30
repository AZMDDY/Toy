# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description: ID管理器 —— 分配，释放ID

message("Compile Utility IDMgr")

set(SRCS_LIST IDMgr.cpp)

add_library(utility_idmgr STATIC ${SRCS_LIST})