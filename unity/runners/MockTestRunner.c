#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER( Mock )
{
    RUN_TEST_CASE( Mock, SampleWriteInput );
    RUN_TEST_CASE( Mock, SampleReadInput );
}
