#include "Mock.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "unity.h"


typedef enum
{
    WRITE,
    READ
} Operation;


typedef struct
{
    Operation kind;
    uint8_t* data;
    uint8_t* returnData;
    uint16_t size;
} Expectation;


static Expectation* expectations = NULL;
static unsigned int setExpectationCount;
static unsigned int getExpectationCount;
static unsigned int maxExpectationCount;
static unsigned int failureAlreadyReported = 0;

static Expectation expected;
static Expectation actual;


// Fail messages
static char* reportExpectWriteWasRead =
    "Expected Write(0x%s), but was Read(0x%s)";

static char* reportExpectReadWasWrite =
    "Expected Read(0x%s) would return 0x%s, but was Write(0x%s)";

static char* reportWriteDoesNotMatch =
    "Expected Write(0x%s), but was Write(0x%s)";

static char* reportReadDoesNotMatch =
    "Expected Read(0x%s) returns 0x%s, but was Read(0x%s)";





static char* reportTooManyWriteExpectations =
    "Mock_ExpectWrite: Too many expectations";

static char* reportTooManyReadExpectations =
    "Mock_ExpectRead: Too many expectations";

static char* reportMockNotInitialized =
    "Mock not initialized, call Mock_Create()";




static const char* reportNoMoreExpectations =
    "R/W %d: No more expectations but was ";

static char* reportWriteButOutOfExpectations =
    "Write(0x%s)";

static char* reportReadButOutOfExpectations =
    "Read(0x%s)";

static const char* reportExpectationNumber =
    "R/W %d: ";

static const char* notAllExpectationsUsed =
    "Expected %u reads/writes but got %u";



void Mock_Create( size_t maxExceptions )
{
    expectations = calloc( maxExceptions, sizeof( Expectation ) );
    setExpectationCount = 0;
    getExpectationCount = 0;
    maxExpectationCount = maxExceptions;
    failureAlreadyReported = 0;
}


void Mock_Destroy()
{
    if ( expectations )
        free( expectations );
    expectations = NULL;
}


static void fail( char* message )
{
    failureAlreadyReported = 1;
    TEST_FAIL_MESSAGE( message );
}


static void failWhenNotInitialized()
{
    if ( expectations == NULL )
        fail( reportMockNotInitialized );
}


static void failWhenNoRoomForExpectations( char* message )
{
    failWhenNotInitialized();
    if ( setExpectationCount >= maxExpectationCount )
        fail( message );
}


static void recordExpectation( Operation kind, uint8_t* data, uint8_t* returnData, uint16_t size )
{
    expectations[ setExpectationCount ].kind = kind;
    expectations[ setExpectationCount ].size = size;
    expectations[ setExpectationCount ].data = data;
    if ( returnData )
    {
        expectations[ setExpectationCount ].returnData = returnData;
    }
    setExpectationCount++;
}


void Mock_ExpectWrite( uint8_t* data, uint16_t size )
{
    failWhenNoRoomForExpectations( reportTooManyWriteExpectations );
    recordExpectation( WRITE, data, NULL, size );
}


void Mock_ExpectReadThenReturn( uint8_t* data, uint8_t* returnData, uint16_t size )
{
    failWhenNoRoomForExpectations( reportTooManyReadExpectations );
    recordExpectation( READ, data, returnData, size );
}


static char* uint8ArrayToHexString(const uint8_t *array, size_t length)
{
    // Allocate memory for the resulting hex string (2 hex chars per byte + null terminator)
    char *hexStr = ( char* )calloc( length * 2 + 1, sizeof( char ) );
    
    // Check if memory allocation is successful
    if ( hexStr == NULL )
    {
        return NULL;
    }

    // Format each byte as two hex digits
    for ( size_t i = 0; i < length; ++i ) 
    {
        sprintf( hexStr + i * 2, "%02X", array[ i ] );
    }

    // Null-terminate the string
    hexStr[ length * 2 ] = '\0';

    return hexStr;
}


static void failWhenNoUnusedExpectations( char* report )
{
    char message[ 100 ];

    if ( getExpectationCount >= setExpectationCount )
    {
        int offset = sprintf( message, reportNoMoreExpectations, getExpectationCount + 1);
        char* hexString = uint8ArrayToHexString( actual.data, actual.size );
        sprintf( message + offset, report, hexString );
        fail( message );
        free( hexString );
    }
}


static void setExpectedAndActual( uint8_t* data, uint16_t size )
{
    expected.data = expectations[ getExpectationCount ].data;
    expected.size = expectations[ getExpectationCount ].size;
    actual.data = data;
    actual.size = size;
}


static void failExpectation( char* failMessage )
{
    char message[ 100 ];

    int offset = sprintf( message, reportExpectationNumber, getExpectationCount + 1);
    char* expectedHexString = uint8ArrayToHexString( expected.data, expected.size );
    char* actualHexString = uint8ArrayToHexString( actual.data, actual.size );
    sprintf( message + offset, failMessage, expectedHexString, actualHexString);
    fail( message );
    free( expectedHexString );
    free( actualHexString );
}


static void failWhen( int condition, char* failMessage )
{
    if ( condition )
        failExpectation( failMessage );
}


static int expectationIsNot( Operation kind )
{
    return kind != expectations[ getExpectationCount ].kind;
}


static int expectedDataIsNot( uint8_t* data, uint16_t size )
{
    return ( memcmp( expected.data, data, size ) != 0 );
}


void Mock_Write( uint8_t* data, uint16_t size )
{
    setExpectedAndActual( data, size );
    failWhenNotInitialized();
    failWhenNoUnusedExpectations( reportWriteButOutOfExpectations );
    failWhen( expectationIsNot( WRITE ),    reportExpectWriteWasRead );
    failWhen( expectedDataIsNot( data, size ),   reportWriteDoesNotMatch  );
    getExpectationCount++;

}


void Mock_Read( uint8_t* data, uint8_t* rxBuff, uint16_t size )
{
    setExpectedAndActual( data, size );
    failWhenNotInitialized();
    failWhenNoUnusedExpectations( reportReadButOutOfExpectations );
    failWhen( expectationIsNot( READ ), reportExpectReadWasWrite );
    failWhen( expectedDataIsNot( data, size ), reportReadDoesNotMatch );

    if ( expectations[ getExpectationCount ].returnData )
    {
        memcpy( rxBuff, expectations[ getExpectationCount ].returnData, size );
    }
    getExpectationCount++;
}


static void failWhenNotAllExpectationsUsed()
{
    if ( getExpectationCount == setExpectationCount )
        return;
    char message[ 100 ];
    sprintf( message, notAllExpectationsUsed, setExpectationCount, getExpectationCount );

    fail( message );
}


void Mock_VerifyComplete()
{
    if ( failureAlreadyReported )
        return;
    failWhenNotAllExpectationsUsed();
}
