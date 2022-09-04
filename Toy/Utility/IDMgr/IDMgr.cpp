// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: ID管理器 —— 分配，释放ID

#include "IDMgr.h"
#include "Log.h"
namespace Utility {
IdMgr::IdMgr(const Range<uint32_t>& idRange)
    : idFlag(idRange.max - idRange.min + 1, false), curIdIter(idFlag.begin()), range(idRange)
{
}

uint32_t IdMgr::AllocId()
{
    // 优先分配未被使用的ID
    for (auto iter = curIdIter; iter != idFlag.end(); ++iter) {
        if (!(*iter)) {
            *iter = true;
            ++curIdIter;
            return static_cast<uint32_t>(iter - idFlag.begin() + range.min);
        }
    }
    // 如果ID都被使用，则使用用被释放过的ID
    for (auto iter = idFlag.begin(); iter != curIdIter; ++iter) {
        if (!(*iter)) {
            *iter = true;
            return static_cast<uint32_t>(iter - idFlag.begin() + range.min);
        }
    }

    LOG_ERROR() << "id is exhausted";
    return range.max;
}

void IdMgr::ReleaseId(uint32_t id)
{
    if (!range.Contain(id)) {
        LOG_ERROR() << "the id: " << id << " is out of range";
        return;
    }
    auto iter = idFlag.begin() + id - range.min;
    if (!(*iter)) {
        LOG_ERROR() << "the id [" << id << "] not exist.";
        return;
    }
    *iter = false;
}

bool IdMgr::IdIsRepeat(uint32_t id)
{
    if (!range.Contain(id)) {
        LOG_ERROR() << "the id: " << id << " is out of range";
        return false;
    }
    auto iter = idFlag.begin() + id - range.min;
    return *iter;
}
}  // namespace Utility