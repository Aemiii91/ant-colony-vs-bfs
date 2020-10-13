#include <gtest/gtest.h>

#include <stdexcept>

#include "../src/graph/graph.h"

using namespace std;

class GraphTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST(GraphTest, addNode) {
  Graph graph;
  Node n(0);
  graph.addNode(n);

  ASSERT_EQ(n.ID, graph.nodelist.front().ID);
}
TEST(GraphTest, getEdgeListSize) {
  Node n(0);
  Node n1(1);
  Edge e(n1.ID, n.ID, 1.2);
  n1.addEdge(e);

  ASSERT_EQ(1, n1.getEdgeListSize());
}

TEST(GraphTest, addEdge) {
  Node n(0);
  Node n1(1);
  Edge e(n1.ID, n.ID, 1.2);
  n1.addEdge(e);
  double weight = n1.getEdge(0).weight;

  ASSERT_EQ(e.scr, n1.getEdge(0).scr);
  ASSERT_EQ(e.weight, weight);
  ASSERT_EQ(e.dist, n1.getEdge(0).dist);
}
