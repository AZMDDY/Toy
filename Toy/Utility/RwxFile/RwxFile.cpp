// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 读写操作文件
#include "RwxFile.h"
#include <fstream>
#include "Basic.h"
#include "Log.h"
namespace Utility {
using namespace std;

int32_t ReadFile(const string& fileName, string& content)
{
    ifstream ifs(fileName, std::ios::binary);
    if (!ifs.good()) {
        LOG_ERROR() << "open file failed. file name: " << fileName;
        return ERR;
    }
    string str((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    content = str;
    return EOK;
}

int32_t WriteFile(const string& fileName, const string& content)
{
    ofstream ofs(fileName, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!ofs.good()) {
        LOG_ERROR() << "open file failed. file name: " << fileName;
        return ERR;
    }
    ofs.write(content.c_str(), static_cast<long>(content.size()));
    return EOK;
}
}  // namespace Utility