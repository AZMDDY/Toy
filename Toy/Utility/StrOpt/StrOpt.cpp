// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 字符串操作

#include "StrOpt.h"
#include "Type.h"
namespace Utility {
void Trim(std::string& str)
{
    if (str.empty()) {
        return;
    }
    auto left = str.find_first_not_of(CHR_SPACE);
    if (left == std::string::npos) {
        left = 0;
    }
    auto right = str.find_last_not_of(CHR_SPACE);
    if (right == std::string::npos) {
        right = str.size();
    }
    if (left == 0 && right == str.size()) {
        return;
    }
    str = str.substr(left, right - left);
}

std::string Trim(const std::string& str)
{
    std::string result = str;
    Trim(result);
    return result;
}
}  // namespace Utility