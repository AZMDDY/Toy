# Copyright (c) 2022 zhengzhibing All rights reserved.
# Description: 第三方库的路径定义

set(ROOT_PATH "${CMAKE_SOURCE_DIR}")
set(TOY_PATH "${ROOT_PATH}/Toy")
set(THIRDPARTY_PATH "${ROOT_PATH}/thirdparty")
set(THIRDPARTY_INC_PATH "${THIRDPARTY_PATH}/include")
set(THIRDPARTY_LIB_PATH "${THIRDPARTY_PATH}/lib")

message("################ path.cmake ####################")
message("ROOT_PATH=${ROOT_PATH}")
message("TOY_PATH=${TOY_PATH}")
message("THIRDPARTY_PATH=${THIRDPARTY_PATH}")
message("THIRDPARTY_INC_PATH=${THIRDPARTY_INC_PATH}")
message("THIRDPARTY_LIB_PATH=${THIRDPARTY_LIB_PATH}")