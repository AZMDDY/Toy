// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 池化 - 内存分配（通过内存池最大分配256 Bytes，超过256 Bytes通过malloc分配）内存池默认大小1M

#include "PoolAlloc.h"
namespace Utility {
static const uint32_t POOL_SIZE = 1 * 1024 * 1024;  // 1M
PoolAlloc::PoolAlloc() : align(8), startFreePos(0), endFreePos(0), heapSize(POOL_SIZE), buffer(nullptr)
{
    endFreePos = startFreePos + heapSize;
    buffer = static_cast<char*>(malloc(heapSize));
}

PoolAlloc::~PoolAlloc()
{
    delete buffer;
}

PoolAlloc& PoolAlloc::Instance()
{
    static PoolAlloc allocator;
    return allocator;
}

void* PoolAlloc::Alloc(size_t n)
{
    if (buffer == nullptr) {
        return nullptr;
    }

    if (n > align * FREE_LISTS_SIZE) {
        return malloc(n);
    }

    if (endFreePos <= startFreePos || n > endFreePos - startFreePos) {
        return nullptr;
    }

    uint32_t pos = (n - 1) / align;
    if (pos >= FREE_LISTS_SIZE) {
        return nullptr;
    }

    if (!freeLists[pos].empty()) {
        void* ptr = freeLists[pos].front();
        freeLists[pos].pop_front();
        return ptr;
    }
    void* ptr = buffer + startFreePos;
    startFreePos += (pos + 1) * align;
    return ptr;
}

void PoolAlloc::Free(void* ptr, size_t n)
{
    if (ptr == nullptr) {
        return;
    }

    if (n > align * FREE_LISTS_SIZE) {
        free(ptr);
    }

    uint32_t pos = (n - 1) / align;
    freeLists[pos].push_front(ptr);
}

}  // namespace Utility