// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: ID管理器 —— 分配，释放ID

#ifndef TOY_IDMGR_H
#define TOY_IDMGR_H
#include <vector>
namespace Utility {
class IdMgr {
public:
    explicit IdMgr(uint32_t idMaxVal = UINT32_MAX);
    IdMgr(const IdMgr&) = default;
    ~IdMgr() = default;
    uint32_t AllocId();  // 优先分配未被使用的ID, 如果ID都被使用，则使用用被释放过的ID
    void ReleaseId(uint32_t id);

private:
    std::vector<bool> idFlag;
    std::vector<bool>::iterator curIdIter;
};
}  // namespace Utility
#endif  // TOY_IDMGR_H
