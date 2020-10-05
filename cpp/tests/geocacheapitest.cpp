#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <regex>
#include "../src/geocacheapi.h"

using namespace std;


class GeocacheAPITest : public ::testing::Test {
    protected:
        void SetUp() override {}

        void TearDown() override{}
};

TEST_F(GeocacheAPITest, SearchTest) {
  GeocacheAPI api;
  
  bool result = api.Search();

  bool expected = true;
  ASSERT_EQ(expected, result);
}
