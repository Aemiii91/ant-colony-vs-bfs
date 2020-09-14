#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

class BasicTest : public ::testing::Test {
    protected:
        void SetUp() override {}

        void TearDown() override {}
};

TEST_F(BasicTest, BasicExample) {
    ASSERT_EQ(1,1);
}
