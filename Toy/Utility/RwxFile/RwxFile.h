// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 读写操作文件

#ifndef TOY_RWXFILE_H
#define TOY_RWXFILE_H
#include <string>
namespace Utility {
int32_t ReadFile(const std::string& fileName, std::string& content);

int32_t WriteFile(const std::string& fileName, const std::string& content);
}  // namespace Utility
#endif  // TOY_RWXFILE_H
