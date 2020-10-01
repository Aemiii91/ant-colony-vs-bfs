#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "../src/rapidjson.h"

using namespace std;


class RapidJsonTest : public ::testing::Test {
    protected:
        void SetUp() override {}

        void TearDown() override{}
};

TEST_F(RapidJsonTest, BasicExample) {
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    rapidjson::Document d;
    d.Parse(json);

    // 2. Modify it by DOM.
    rapidjson::Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    // output should be what is seen on the comment just below
    // Output {"project":"rapidjson","stars":11}
    string expected = "{\"project\":\"rapidjson\",\"stars\":11}";
    ASSERT_EQ(expected, buffer.GetString());
}
