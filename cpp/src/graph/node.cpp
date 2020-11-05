#include "node.h"
void Node::AddEdge(Edge e) {
	edgeList.emplace_back(e);
}
// Makes sure that people use .at() for bound check (this is slower bu safer)
Edge Node::GetEdge(int ID) {
	return edgeList.at(ID);
}
size_t Node::GetEdgeListSize() {
	return edgeList.size();
}
