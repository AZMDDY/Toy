// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 池化 - 内存分配（通过内存池最大分配256 Bytes，超过256 Bytes通过malloc分配）

#ifndef TOY_POOLALLOC_H
#define TOY_POOLALLOC_H
#include <array>
#include <forward_list>
namespace Utility {
const uint32_t FREE_LISTS_SIZE = 16;  // free list size
class PoolAlloc {
public:
    PoolAlloc(const PoolAlloc&) = delete;
    PoolAlloc& operator=(const PoolAlloc&) = delete;

    static PoolAlloc& Instance();
    void* Alloc(size_t n);
    void Free(void* ptr, size_t n);

private:
    PoolAlloc();
    ~PoolAlloc();

private:
    // 8, 16, ..., 8*15, 8*16 Bytes
    std::array<std::forward_list<void*>, FREE_LISTS_SIZE> freeLists;
    const uint32_t align;
    uint32_t startFreePos;
    uint32_t endFreePos;
    uint32_t heapSize;
    char* buffer;
};
}  // namespace Utility
#endif  // TOY_POOLALLOC_H
