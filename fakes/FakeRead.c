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
static size_t   nextRead8ArrMaxSize = 0;
static size_t   nextRead8ArrSize = 0;

static uint8_t* lastCmd8Arr  = NULL;
static size_t   lastCmd8ArrMaxSize = 0;
static size_t   lastCmd8ArrSize = 0;


void FakeRead_Create( size_t maxNextRead8ArrSize, size_t maxLastCmd8ArrSize )
{
    nextRead16 = 0;
    lastCmd16  = 0;

    nextRead32 = 0;
    lastCmd32  = 0;

    nextRead8ArrSize = 0;
    nextRead8ArrMaxSize = maxNextRead8ArrSize;
    if ( maxNextRead8ArrSize )
    {
        nextRead8Arr = ( uint8_t* )calloc( maxNextRead8ArrSize, sizeof( uint8_t ) );
    }

    lastCmd8ArrSize = 0;
    lastCmd8ArrMaxSize = maxLastCmd8ArrSize;
    if ( maxLastCmd8ArrSize )
    {
        lastCmd8Arr = ( uint8_t* )calloc( maxLastCmd8ArrSize, sizeof( uint8_t ) );
    }
}

void FakeRead_Destroy()
{
    if ( nextRead8Arr )
    {
        free( nextRead8Arr );
        nextRead8Arr = NULL;
    }
    if ( lastCmd8Arr )
    {
        free( lastCmd8Arr );
        lastCmd8Arr = NULL;
    }
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
    if ( fakeReading && ( nextRead8ArrMaxSize - nextRead8ArrSize >= size ) )
    {
        memcpy( nextRead8Arr + nextRead8ArrSize, fakeReading, size );
        nextRead8ArrSize += size;
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


size_t FakeRead_GetLastCmd8ArrSize()
{
    return lastCmd8ArrSize;
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
    // Store cmd
    if ( lastCmd8Arr && cmd && ( lastCmd8ArrMaxSize - lastCmd8ArrSize >= size ) )
    {
        memcpy( lastCmd8Arr + lastCmd8ArrSize, cmd, size );
        lastCmd8ArrSize += size;
    }

    // Copy over nextRead
    if ( nextRead8Arr && rxBuff && ( size <= nextRead8ArrSize ) )
    {
        memcpy( rxBuff, nextRead8Arr, size );
    }
}

// Same as above but allows for cmd and rxBuff to have different sizes
void FakeRead_Read8ArrDiffSize( uint8_t* cmd, uint16_t cmdSize, uint8_t* rxBuff, uint16_t rxSize )
{
    // Store cmd
    if ( lastCmd8Arr && cmd && ( lastCmd8ArrMaxSize - lastCmd8ArrSize >= cmdSize ) )
    {
        memcpy( lastCmd8Arr + lastCmd8ArrSize, cmd, cmdSize );
        lastCmd8ArrSize += cmdSize;
    }

    // Copy over nextRead
    if ( nextRead8Arr && rxBuff && ( rxSize <= nextRead8ArrSize ) )
    {
        memcpy( rxBuff, nextRead8Arr, rxSize );
    }
}
