#include "FakeRead.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static uint16_t nextRead16 = 0;
static uint16_t lastCmd16  = 0;

static uint32_t nextRead32 = 0;
static uint32_t lastCmd32  = 0;

static uint32_t nextRead32VoidParameter = 0;

static uint8_t* nextRead8Arr = NULL;
static uint8_t* lastCmd8Arr  = NULL;


void FakeRead_Create()
{
    nextRead16 = 0;
    lastCmd16  = 0;

    nextRead32 = 0;
    lastCmd32  = 0;

    free( nextRead8Arr );
    nextRead8Arr = NULL;
    free( lastCmd8Arr );
    lastCmd8Arr = NULL;
}


void FakeRead_SetNextReading16(uint16_t fakeReading)
{
    nextRead16 = fakeReading;
}


void FakeRead_SetNextReading32(uint32_t fakeReading)
{
    nextRead32 = fakeReading;
}


void FakeRead_SetNextReading32VoidParameter( uint32_t fakeReading )
{
    nextRead32VoidParameter = fakeReading;
}


void FakeRead_SetNextReading8Arr( uint8_t* fakeReading, uint16_t size )
{
    if ( fakeReading )
    {
        nextRead8Arr = ( uint8_t* )calloc( size, sizeof( uint8_t ) );
        memcpy( nextRead8Arr, fakeReading, size );
    }
}


uint16_t FakeRead_GetLastCmd16()
{
    return lastCmd16;
}


uint32_t FakeRead_GetLastCmd32()
{
    return lastCmd32;
}


uint8_t* FakeRead_GetLastCmd8Arr()
{
    return lastCmd8Arr;
}


uint16_t FakeRead_Read16(uint16_t cmd)
{
    lastCmd16 = cmd;
    return nextRead16;
}


uint32_t FakeRead_Read32(uint32_t cmd)
{
    lastCmd32 = cmd;
    return nextRead32;
}


uint32_t FakeRead_Read32VoidParameter()
{
    return nextRead32VoidParameter;
}


void FakeRead_Read8Arr( uint8_t* cmd, uint8_t* rxBuff, uint16_t size )
{
    if ( cmd && rxBuff && nextRead8Arr )
    {
        lastCmd8Arr = ( uint8_t* )calloc( size, sizeof( uint8_t ) );
        memcpy( lastCmd8Arr, cmd, size );

        memcpy( rxBuff, nextRead8Arr, size );
    }
}

