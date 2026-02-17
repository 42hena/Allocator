#include "MemoryUtil.h"

#include <iostream>

int main()
{
    // MAlloc Test
    char* ptr = (char*)MAlloc(9);
    
    char* tmp = ptr - 8;    // 8byte 체크에서 걸림
    // char* tmp = ptr - 7;    // 1byte 체크에서 걸림
    *tmp = 1;
    MFree(ptr);
}
