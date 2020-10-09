#include <iostream>
#include <string>
#include <vector>

#include "edge.h"
using namespace std;
class Node {
 public:
  Node(int id) : ID(id) {}  // Give node identifier
  int ID;  // used as identifier (should be set to the same as the node
  vector<Edge> edgeList;  // used to store edges the Node
  void addEdge(Edge e);

 private:
  // This is used to print the object in a nice way
  friend ostream& operator<<(ostream& out, const Node& n) {
    cout << "ID: " << n.ID << setw(2);

    return out;
  };
};
