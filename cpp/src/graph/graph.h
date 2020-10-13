#include <iostream>
#include <vector>

#include "node.h"
using namespace std;
class Graph {
 public:
  vector<Node> nodelist;
  vector<Edge> edgeList;
  void addNode(Node n);
  void ImFastLetMeShowYou();
  void print();
};
