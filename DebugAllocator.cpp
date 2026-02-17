#include "DebugAllocator.h"

#include <iostream>
#include <Windows.h>

void DebugAllocator::CheckSystemInfo()
{
    SYSTEM_INFO info;

    GetSystemInfo(&info);

    // Check current System Info
    if (eMemorySize_PAGE_SIZE != info.dwPageSize || eMemorySize_RESERVE_SIZE != info.dwAllocationGranularity)
    {
        std::cout << "Allocator Warning!!! PageSize : " << info.dwPageSize << ", ReserveSize : " << info.dwAllocationGranularity << '\n';
        __debugbreak();
    }
}

void* DebugAllocator::Alloc(size_t size)
{
    const long long allocSize = ((eMemorySize_PAGE_SIZE - 1) + size) / eMemorySize_PAGE_SIZE * eMemorySize_PAGE_SIZE;
    void* base = VirtualAlloc(nullptr, allocSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    unsigned char* objectPos = reinterpret_cast<unsigned char*>(base) + allocSize - size;

    // std::cout << "Alloc Base:" << base << ", Return Ptr:" << (void*)objectPos << '\n';

    return objectPos;
}

void DebugAllocator::Free(void* ptr)
{
    unsigned char* base = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned long long>(ptr) & ~(eMemorySize_PAGE_SIZE - 1));

    // std::cout << "Free Base:" << (void*)base << ", Current Ptr:" << ptr << '\n';
    unsigned char* start = base;
    size_t size = reinterpret_cast<unsigned char*>(ptr) - base;
    while (size >= 8)
    {
        uint64_t value = *reinterpret_cast<uint64_t*>(start);

        if (value != 0)
        {
            std::cout << "8 byte check\n";
            __debugbreak();
        }

        start += 8;
        size -= 8;
    }

    while (size > 0)
    {
        if (*start != 0)
        {
            std::cout << "1 byte check\n";
            __debugbreak();
        }

        start++;
        size--;
    }

    // MEM_RELEASEÀÎ °æ¿ì 0(MSDN)
    VirtualFree(base, 0, MEM_RELEASE);
}
