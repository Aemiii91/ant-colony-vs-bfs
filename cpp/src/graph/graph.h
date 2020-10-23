#include <iostream>
#include <vector>

#include "node.h"
class Graph {
public:
  std::vector<Node> nodelist;
  std::vector<Edge> edgeList;
  /**
   * As obvious as the name is: get size of graph
   *
   * @return number of elements in graph
   */
  int GetGraphSize();
  /**
   * Obvious, adds a node to the graph
   *
   * When this method is used the graph's respective edges are also added to the
   * graph's edgeList
   */
  void AddNode(Node n);
  /**
   * Test method for initialized a graph, mostly for fun
   */
  void ImFastLetMeShowYou();
  /**
   * Prints the graph in a human-readable way
   */
  void Print();
};
