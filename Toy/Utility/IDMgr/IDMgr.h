// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: ID管理器 —— 分配，释放ID，ID分配范围：[min, max]，超出范围时为max

#ifndef TOY_IDMGR_H
#define TOY_IDMGR_H
#include <vector>
#include "Basic.h"
namespace Utility {
class IdMgr {
public:
    explicit IdMgr(const Range<uint32_t>& idRange = {0, UINT32_MAX});
    IdMgr(const IdMgr&) = default;
    ~IdMgr() = default;
    uint32_t AllocId();  // 优先分配未被使用的ID, 如果ID都被使用，则使用被释放过的ID
    void ReleaseId(uint32_t id);
    bool IdIsRepeat(uint32_t id);

private:
    std::vector<bool> idFlag;
    std::vector<bool>::iterator curIdIter;
    Range<uint32_t> range;
};
}  // namespace Utility
#endif  // TOY_IDMGR_H
