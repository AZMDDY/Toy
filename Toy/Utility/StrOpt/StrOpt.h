// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 字符串操作

#ifndef TOY_STROPT_H
#define TOY_STROPT_H
#include <string>
namespace Utility {
// 裁剪字符串两端的空格
void Trim(std::string& str);
std::string Trim(const std::string& str);
}

#endif  // TOY_STROPT_H
