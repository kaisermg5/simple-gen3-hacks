#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include <types.h>


struct Coords16
{
    s16 x;
    s16 y;
};

struct UCoords16
{
    u16 x;
    u16 y;
};


extern u16 Random();
extern u32 __umodsi3(u32 x, u32 y);
extern s32 __modsi3(s32 x, s32 y);

#include <decompress.h>
#include <malloc.h>


#endif // GUARD_GLOBAL_H
