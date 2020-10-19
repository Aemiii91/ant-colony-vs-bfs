#include "node.h"
void Node::addEdge(Edge e) {
  edgeList.emplace_back(e);
}
// Makes sure that people use .at() for bound check (this is slower bu safer)
Edge Node::getEdge(int ID) {
  return edgeList.at(ID);
}
size_t Node::getEdgeListSize() {
  return edgeList.size();
}
