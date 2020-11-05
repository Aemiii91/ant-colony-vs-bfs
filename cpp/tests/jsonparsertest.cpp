#include "../src/jsonparser.h"
#include <gtest/gtest.h>

#include <stdexcept>

using namespace std;

class JsonParserTest : public ::testing::Test {
  protected:
	void SetUp() override {}

	void TearDown() override {}
};

TEST(JsonParserTest, ParseData) {
	JsonParser parser;
	Graph graph;

	graph = parser.ParseData("../data/jsontest");

	double expected = 74819.55;
	double result = graph.nodelist.at(0).GetEdge(0).weight;

	ASSERT_EQ(expected, result);
}

TEST(JsonParserTest, ConnectNodes) {
	JsonParser parser;
	Graph graph;

	graph = parser.ParseData("../data/jsontest_mockup");
	double expected = 0.00000000000001;
	double result = graph.nodelist.at(0).GetEdge(2).weight;

	ASSERT_EQ(expected, result);
}
