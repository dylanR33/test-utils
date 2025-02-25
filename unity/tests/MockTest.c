#include "Mock.h"

#include "unity.h"
#include "unity_fixture.h"

#include <stdint.h>


TEST_GROUP( Mock );


TEST_SETUP( Mock )
{
    Mock_Create( 4 );
}


TEST_TEAR_DOWN( Mock )
{
    Mock_Destroy();
}

TEST( Mock, SampleWriteInput )
{
    uint8_t firstWrite[]  = { 0x01, 0x02 };
    uint8_t secondWrite[] = { 0x03, 0x04 };
    Mock_ExpectWrite( firstWrite, sizeof( firstWrite ) );
    Mock_ExpectWrite( secondWrite, sizeof( secondWrite ) );

    Mock_Write( firstWrite, sizeof( firstWrite ) );
    Mock_Write( secondWrite, sizeof( secondWrite ) );
}

TEST( Mock, SampleReadInput )
{
    uint8_t firstReadCmd[]  = { 0x0A, 0x0B };
    uint8_t secondReadCmd[] = { 0x0C, 0x0D };
    uint8_t returnData[] = { 0xFF, 0xFF };
    Mock_ExpectReadThenReturn( firstReadCmd, NULL, sizeof( firstReadCmd ) );
    Mock_ExpectReadThenReturn( secondReadCmd, returnData, sizeof( secondReadCmd ) );

    uint8_t rxBuff[2];
    Mock_Read( firstReadCmd, rxBuff, sizeof( firstReadCmd ) );
    Mock_Read( secondReadCmd, rxBuff, sizeof( secondReadCmd ) );

    TEST_ASSERT_EQUAL_UINT8_ARRAY( returnData, rxBuff, sizeof( returnData ) );
}
