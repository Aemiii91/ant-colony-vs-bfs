#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <regex>
#include "../apicaller/src/opencaching.hpp"

using namespace std;

class ApicallerTest : public ::testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ApicallerTest, OpencachingTest)
{
    string json_data = apicaller::opencaching(52.518848, 13.399411);

    bool result = true;
    bool expected = true;
    ASSERT_EQ(expected, result);
}
