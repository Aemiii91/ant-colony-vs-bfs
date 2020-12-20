#include "node.h"
void Node::AddEdge(Edge e) {
	edgeList.emplace_back(e);
}
Edge Node::GetEdge(int ID) {
	return edgeList.at(ID);
}
size_t Node::GetEdgeListSize() {
	return edgeList.size();
}
bool Node::EdgeListCompare(const Node &foo) {
	for (auto edgeI : this->edgeList) {
		for (auto edgeJ : foo.edgeList) {
			if (edgeI.dist != edgeJ.dist || edgeI.weight != edgeJ.weight)
				return false;
		}
	}
	return true;
}
