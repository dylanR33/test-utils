#include "FakeRead.h"

#include "unity.h"
#include "unity_fixture.h"

#include <stdint.h>

#define SIZE 4

TEST_GROUP( FakeRead );


TEST_SETUP( FakeRead )
{
    FakeRead_Create( SIZE, SIZE );
}

TEST_TEAR_DOWN( FakeRead )
{
    FakeRead_Destroy();
}

TEST( FakeRead, Create )
{
    TEST_ASSERT_EQUAL( 0, FakeRead_GetLastCmd16() );
    TEST_ASSERT_EQUAL( 0, FakeRead_Read16( 0 ) );

    TEST_ASSERT_EQUAL( 0, FakeRead_GetLastCmd32() );
    TEST_ASSERT_EQUAL( 0, FakeRead_Read32( 0 ) );

    TEST_ASSERT_NOT_NULL( FakeRead_GetLastCmd8Arr() );
}


TEST( FakeRead, SetNextReading )
{
    FakeRead_SetNextReading16( 2 );
    TEST_ASSERT_EQUAL( 2, FakeRead_Read16( 0 ) );

    FakeRead_SetNextReading32( 5 );
    TEST_ASSERT_EQUAL( 5, FakeRead_Read32( 0 ) );

    uint8_t fake[ SIZE ] = { 1, 2, 3 };
    uint8_t cmd [ SIZE ];
    uint8_t rx  [ SIZE ];
    FakeRead_SetNextReading8Arr( fake, SIZE );
    FakeRead_Read8Arr( cmd, rx, SIZE );
    TEST_ASSERT_EQUAL_UINT8_ARRAY( fake, rx, SIZE );
}

TEST( FakeRead, GetLastCmd )
{
    FakeRead_Read16( 3 );
    TEST_ASSERT_EQUAL( 3, FakeRead_GetLastCmd16() );

    FakeRead_Read32( 5 );
    TEST_ASSERT_EQUAL( 5, FakeRead_GetLastCmd32() );

    uint8_t fake[ SIZE ] = { 1, 2, 3 };
    uint8_t cmd [ SIZE ];
    uint8_t rx  [ SIZE ];
    FakeRead_SetNextReading8Arr( fake, SIZE );
    FakeRead_Read8Arr( cmd, rx, SIZE );
    TEST_ASSERT_EQUAL_UINT8_ARRAY( cmd, FakeRead_GetLastCmd8Arr(), FakeRead_GetLastCmd8ArrSize() );
}

