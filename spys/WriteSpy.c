#include "WriteSpy.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static uint16_t lastWrite16 = 0;
static uint32_t lastWrite32 = 0;
static uint8_t  lastWrite8  = 0;

static uint8_t* lastWrite8Arr = NULL;
static size_t   lastWrite8ArrMaxSize = 0;
static size_t   lastWrite8ArrSize = 0;

void WriteSpy_Create( size_t maxWriteCount8Arr )
{
    lastWrite16 = 0;
    lastWrite32 = 0;
    lastWrite8  = 0;

    lastWrite8ArrSize = 0;
    lastWrite8ArrMaxSize = maxWriteCount8Arr;
    if ( maxWriteCount8Arr )
    {
        lastWrite8Arr = ( uint8_t* )calloc( maxWriteCount8Arr, sizeof( uint8_t ) );
    }
}

void WriteSpy_Destroy()
{
    if ( lastWrite8Arr )
    {
        free( lastWrite8Arr );
        lastWrite8Arr = NULL;
    }
}

uint16_t WriteSpy_GetLastWrite16()
{
    return lastWrite16;
}

uint32_t WriteSpy_GetLastWrite32()
{
    return lastWrite32;
}

uint8_t WriteSpy_GetLastWrite8()
{
    return lastWrite8;
}

uint8_t* WriteSpy_GetLastWrite8Arr()
{
    return lastWrite8Arr;
}

size_t WriteSpy_GetLastWrite8ArrSize()
{
    return lastWrite8ArrSize;
}

void WriteSpy_Write16( uint16_t cmd )
{
    lastWrite16 = cmd;
}

void WriteSpy_Write32( uint32_t cmd )
{
    lastWrite32 = cmd;
}

void WriteSpy_Write8( uint8_t cmd )
{
    lastWrite8 = cmd;
}

void WriteSpy_Write8Arr( uint8_t* cmd , uint16_t size )
{
    if ( cmd && ( lastWrite8ArrMaxSize - lastWrite8ArrSize >= size ) )
    {
        memcpy( lastWrite8Arr + lastWrite8ArrSize, cmd, size );
        lastWrite8ArrSize += size;
    }
}

