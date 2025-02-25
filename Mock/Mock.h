#ifndef __MOCK_H__
#define __MOCK_H__

#include <stdint.h>
#include <stddef.h>


void Mock_Create( size_t maxExceptions );

void Mock_Destroy();

void Mock_ExpectWrite( uint8_t* data, uint16_t size );

void Mock_ExpectReadThenReturn( uint8_t* data, uint8_t* returnData, uint16_t size );

void Mock_Write( uint8_t* data, uint16_t size );

void Mock_Read( uint8_t* data, uint8_t* rxBuff, uint16_t size );

void Mock_VerifyComplete();

#endif
