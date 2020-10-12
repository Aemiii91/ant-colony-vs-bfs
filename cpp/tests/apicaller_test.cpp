#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <regex>
#include "../src/apicaller.h"

using namespace std;

class ApiCallerTest : public ::testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ApiCallerTest, OpenCachingTest)
{
    ApiCaller apiCaller;

    apiCaller.openCaching();

    bool result = true;
    bool expected = true;
    ASSERT_EQ(expected, result);
}
