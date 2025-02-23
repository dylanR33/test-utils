#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER( FakeRead )
{
    RUN_TEST_CASE( FakeRead, SetNextReading );
    RUN_TEST_CASE( FakeRead, GetLastCmd );
    RUN_TEST_CASE( FakeRead, Create );
}
