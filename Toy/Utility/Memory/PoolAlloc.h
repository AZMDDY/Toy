// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 内存池

#ifndef TOY_POOLALLOC_H
#define TOY_POOLALLOC_H
#include <array>
#include <forward_list>
#include "Type.h"
#include "Log.h"
namespace Utility {
// 内存池大小：poolSize Bytes，内存池的最大分配内存单元：freeListSize * 8 Bytes
template<uint32_t poolSize = 1 * 1024 * 1024, uint32_t freeListSize = 16>
class PoolAlloc {
public:
    PoolAlloc() : ALIGN(8), MAX_MEM_UINT_SIZE(ALIGN * freeListSize), startFreePos(0), endFreePos(0), buffer(nullptr) {}
    ~PoolAlloc() { free(buffer); }

    PoolAlloc(const PoolAlloc&) = delete;
    PoolAlloc& operator=(const PoolAlloc&) = delete;

    uint32_t Init()
    {
        if (buffer != nullptr) {
            LOG_ERROR() << "already init.";
            return ERR;
        }

        buffer = static_cast<char*>(malloc(poolSize));
        if (buffer == nullptr) {
            LOG_ERROR() << "malloc failed. size: " << poolSize;
            return ERR;
        }
        startFreePos = 0;
        endFreePos = startFreePos + poolSize - 1;
        return EOK;
    }

    void* Alloc(size_t n)
    {
        if (n > MAX_MEM_UINT_SIZE) {
            LOG_INFO() << "the pool can't alloc " << n << " bytes. max alloc size: " << MAX_MEM_UINT_SIZE
                       << " bytes. malloc it: " << n;
            return malloc(n);
        }

        uint32_t pos = (n - 1) / ALIGN;

        // 优先从回收的内存中分配
        if (!freeList[pos].empty()) {
            void* ptr = freeList[pos].front();
            freeList[pos].pop_front();
            return ptr;
        }

        if (endFreePos <= startFreePos || n > endFreePos - startFreePos) {
            LOG_ERROR() << "insufficient remaining memory";
            return nullptr;
        }
        void* ptr = static_cast<void*>(buffer + startFreePos);
        startFreePos += (pos + 1) * ALIGN;
        return ptr;
    }

    void Free(void*& ptr, size_t n)
    {
        if (n > MAX_MEM_UINT_SIZE) {
            free(ptr);
        }

        uint32_t pos = (n - 1) / ALIGN;
        freeList[pos].push_front(ptr);
        ptr = nullptr;
    }

    uint32_t Size() const { return poolSize; }

    uint32_t RemainSize() const { return endFreePos - startFreePos + 1; }

    uint32_t MaxMemUnitSize() const { return MAX_MEM_UINT_SIZE; }

private:
    const uint32_t ALIGN;
    const uint32_t MAX_MEM_UINT_SIZE;

    // 8, 16, ..., 8*15, 8*16 Bytes
    std::array<std::forward_list<void*>, freeListSize> freeList;
    uint32_t startFreePos;
    uint32_t endFreePos;
    char* buffer;
};
}  // namespace Utility
#endif  // TOY_POOLALLOC_H
