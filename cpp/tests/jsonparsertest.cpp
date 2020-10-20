#include <gtest/gtest.h> 
#include "../src/jsonparser.h"

#include <stdexcept>

using namespace std;

class JsonParserTest : public ::testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST(JsonParserTest, ParseData)
{
    JsonParser parser;
    Graph graph;
    
    graph = parser.ParseData("../data/jsontest");
    
    double expected = 74819.55;
    double result = graph.nodelist.at(0).getEdge(0).weight;
    
    ASSERT_EQ(expected, result);
}
