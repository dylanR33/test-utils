#include "WriteSpy.h"

#include "unity.h"
#include "unity_fixture.h"

#include <stdint.h>


TEST_GROUP( WriteSpy );


TEST_SETUP( WriteSpy )
{
    WriteSpy_Create();
}


TEST_TEAR_DOWN( WriteSpy )
{
}


TEST( WriteSpy, Create )
{
    TEST_ASSERT_EQUAL( 0, WriteSpy_GetLastWrite16() );
    TEST_ASSERT_EQUAL( 0, WriteSpy_GetLastWrite32() );
}


TEST( WriteSpy, GetLastWrite )
{
    WriteSpy_Write16( 4 );
    TEST_ASSERT_EQUAL( 4, WriteSpy_GetLastWrite16() );

    WriteSpy_Write32( 5 );
    TEST_ASSERT_EQUAL( 5, WriteSpy_GetLastWrite32() );

    uint8_t cmd[] = { 1, 2, 3};
    WriteSpy_Write8Arr( cmd, sizeof( cmd ) );
    TEST_ASSERT_EQUAL_UINT8_ARRAY( cmd, WriteSpy_GetLastWrite8Arr(), sizeof( cmd ) );
} 

