#ifndef __FAKE_READ_H__
#define __FAKE_READ_H__

#include <stdint.h>

void FakeRead_Create();

void FakeRead_SetNextReading16( uint16_t fakeReading );

void FakeRead_SetNextReading32( uint32_t fakeReading );

void FakeRead_SetNextReading32VoidParameter( uint32_t fakeReading );

void FakeRead_SetNextReading8Arr( uint8_t* fakeReading, uint16_t size );

uint16_t FakeRead_GetLastCmd16();

uint32_t FakeRead_GetLastCmd32();

uint8_t* FakeRead_GetLastCmd8Arr();

uint16_t FakeRead_Read16( uint16_t cmd );

uint32_t FakeRead_Read32( uint32_t cmd );

uint32_t FakeRead_Read32VoidParameter();

void FakeRead_Read8Arr( uint8_t* cmd, uint8_t* rxBuff, uint16_t size );

#endif

