#include <gtest/gtest.h>

#include <stdexcept>

#include "../src/graph/graph.h"

using namespace std;

class GraphTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(GraphTest, AddNodeTest) {
  Graph graph;
  Node n(0);
  graph.AddNode(n);

  ASSERT_EQ(n.ID, graph.nodelist.front().ID);
}
TEST_F(GraphTest, GetEdgeListSizeTest) {
  Node n(0);
  Node n1(1);
  Edge e(n1.ID, n.ID, 1.2);
  n1.AddEdge(e);

  ASSERT_EQ(1, n1.GetEdgeListSize());
}

TEST_F(GraphTest, AddEdgeTest) {
  Node n(0);
  Node n1(1);
  Edge e(n1.ID, n.ID, 1.2);
  n1.AddEdge(e);
  double weight = n1.GetEdge(0).weight;

  ASSERT_EQ(e.scr, n1.GetEdge(0).scr);
  ASSERT_EQ(e.weight, weight);
  ASSERT_EQ(e.dist, n1.GetEdge(0).dist);
}
