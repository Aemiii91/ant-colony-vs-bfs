#include <iostream>
#include <string>
#include <vector>

#include "edge.h"
using namespace std;
class Node {
 public:
  Node(int id) : ID(id) {}
  int ID;                 // used as identifier
  vector<Edge> edgeList;  // used to store edges the Node

 private:
  // This is used to print the object in a nice way
  friend ostream& operator<<(ostream& out, const Node& n) {
    cout << "ID: " << n.ID << setw(2);

    return out;
  };
};
