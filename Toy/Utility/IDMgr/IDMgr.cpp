// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: ID管理器 —— 分配，释放ID

#include "IDMgr.h"
#include "Log.h"
namespace Utility {
IdMgr::IdMgr(uint32_t idMaxVal) : idFlag(idMaxVal, false), curIdIter(idFlag.begin()) {}

uint32_t IdMgr::AllocId()
{
    // 优先分配未被使用的ID
    for (auto iter = curIdIter; iter != idFlag.end(); ++iter) {
        if (!(*iter)) {
            *iter = true;
            ++curIdIter;
            return static_cast<uint32_t>(iter - idFlag.begin());
        }
    }
    // 如果ID都被使用，则使用用被释放过的ID
    for (auto iter = idFlag.begin(); iter != curIdIter; ++iter) {
        if (!(*iter)) {
            *iter = true;
            return static_cast<uint32_t>(iter - idFlag.begin());
        }
    }

    LOG_ERROR() << "id is exhausted";
    return UINT32_MAX;
}

void IdMgr::ReleaseId(uint32_t id)
{
    auto iter = idFlag.begin() + id;
    if (!(*iter)) {
        LOG_ERROR() << "the id [" << id << "] not exist.";
        return;
    }
    *iter = false;
}
}