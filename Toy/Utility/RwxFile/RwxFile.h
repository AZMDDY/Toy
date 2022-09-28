// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 读写操作文件

#ifndef TOY_RWXFILE_H
#define TOY_RWXFILE_H
#include <string>
#include <fstream>
#include "Log.h"
namespace Utility {
int32_t ReadFile(const std::string& fileName, std::string& content);
int32_t WriteFile(const std::string& fileName, const std::string& content);

template<class T>
int32_t ReadFile(const std::string& fileName, T* data, uint32_t dataLen = sizeof(T))
{
    std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
    if (!ifs.good()) {
        LOG_ERROR() << "open file failed. file name: " << fileName;
        return ERR;
    }
    ifs.read(reinterpret_cast<char*>(data), dataLen);
    return EOK;
}

template<class T>
int32_t WriteFile(const std::string& fileName, const T* data, uint32_t dataLen = sizeof(T))
{
    std::ofstream ofs(fileName, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!ofs.good()) {
        LOG_ERROR() << "open file failed. file name: " << fileName;
        return ERR;
    }
    ofs.write(reinterpret_cast<const char*>(data), dataLen);
    return EOK;
}
}  // namespace Utility
#endif  // TOY_RWXFILE_H
