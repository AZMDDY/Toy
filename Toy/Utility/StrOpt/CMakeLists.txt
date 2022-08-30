# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description:

message("Compile Utility StrOpt")

set(SRCS_LIST StrOpt.cpp)

add_library(utility_stropt STATIC ${SRCS_LIST})