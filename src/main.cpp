#include "A_Star.h"

#ifdef TEST_RUN
#include "gtest/gtest.h"
#include "FunctionalTests.h"
#include "PerformanceTests.h"
#include "cMeter.cpp"
#include "cMeterDataDump.cpp"
#endif

int main(int argc, char** argv)
{
    #ifdef TEST_RUN
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    #else
    return 0;
    #endif // TEST_RUN
}
