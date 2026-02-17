#pragma once

#include "DebugAllocator.h"

#include <type_traits>

#ifndef DEFAULT
    #define MAlloc(allocSize)   DebugAllocator::Alloc(allocSize)
    #define MFree(ptr)          DebugAllocator::Free(ptr)
#elif
    #define MAlloc(size)        malloc(size)
    #define MFree(ptr)          free(ptr)
#endif

template<typename Type, typename ...Ts>
Type* MNew(Ts&&... args)
{
    Type* memoryBlock = static_cast<Type*>(MAlloc(sizeof(Type)));

    new(memoryBlock) Type(std::forward<Ts>(args)...);
    return memoryBlock;
}

template<typename Type>
void MDelete(Type* objectPtr)
{
    objectPtr->~Type();
    MFree(objectPtr);
}
