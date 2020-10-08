#include <iostream>
#include <vector>

#include "node.h"
using namespace std;
class Graph {
 public:
  vector<Node> nodelist;
  void addNode(Node n);
  void biAddEdge(Node n, Edge e, Node dist);
  void direcAddEdge(Node n, Edge e);
  void ImFastLetMeShowYou();
  void print();
};
