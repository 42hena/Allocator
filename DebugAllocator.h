#pragma once

class DebugAllocator
{
    enum eMemorySize
    {
        eMemorySize_PAGE_SIZE = 0x1000,
        eMemorySize_RESERVE_SIZE = 0x10000
    };

#pragma region 특수 멤버 함수
public:
    DebugAllocator()                                    = delete;
    ~DebugAllocator()                                   = delete;

    DebugAllocator(const DebugAllocator&)               = delete;
    DebugAllocator& operator=(const DebugAllocator&)    = delete;
    DebugAllocator(DebugAllocator&&)                    = delete;
    DebugAllocator& operator=(DebugAllocator&&)         = delete;
#pragma endregion

public:
    static void     CheckSystemInfo();
    
public:
    static void*    Alloc(size_t allocSize);
    static void     Free(void* ptr);
};
