# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description:  日志输出接口

message("Compile Utility Log")

set(SRCS_LIST Log.cpp)

add_library(utility_log STATIC ${SRCS_LIST})