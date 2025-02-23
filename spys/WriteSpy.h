#ifndef __WRITE_SPY_H__
#define __WRITE_SPY_H__

#include <stdint.h>

void WriteSpy_Create();

uint16_t WriteSpy_GetLastWrite16();

uint32_t WriteSpy_GetLastWrite32();

uint8_t WriteSpy_GetLastWrite8();

uint8_t* WriteSpy_GetLastWrite8Arr();

void WriteSpy_Write16( uint16_t cmd );

void WriteSpy_Write32( uint32_t cmd );

void WriteSpy_Write8( uint8_t cmd );

void WriteSpy_Write8Arr( uint8_t* cmd , uint32_t size );

#endif

