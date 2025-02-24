#include "WriteSpy.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static uint16_t lastWrite16 = 0;
static uint32_t lastWrite32 = 0;
static uint8_t  lastWrite8  = 0;

static uint8_t* lastWriteArr = NULL;

void WriteSpy_Create()
{
    lastWrite16 = 0;
    lastWrite32 = 0;
    lastWrite8  = 0;
    
    free( lastWriteArr );
    lastWriteArr = NULL;
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
    return lastWriteArr;
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
    if ( cmd )
    {
        lastWriteArr = ( uint8_t* )calloc( size, sizeof( uint8_t ) );
        memcpy( lastWriteArr, cmd, size );
    }
}

