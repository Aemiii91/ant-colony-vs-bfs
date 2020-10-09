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
TEST(GraphTest, addEdge) {
  // set up
  Graph graph;
  Node n(0);
  Node n2(1);
  graph.addNode(n);
  graph.addNode(n2);

  Edge e(1.2, n.ID);
  graph.direcAddEdge(n2, e);

  ASSERT_EQ(n.ID, graph.nodelist.at(n2.ID).edgeList.front().dist);
}
