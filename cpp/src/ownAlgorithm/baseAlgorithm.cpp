#include "baseAlgorithm.h"

double BaseAlgorithm::TravelTime(Node *n1, Node *n2) {
	double cost = 0.0;
	for (auto edge : n1->edgeList) {
		if (edge.dist == n2->ID) {
			cost = edge.weight;
			break;
		}
	}
	return cost;
}

Node BaseAlgorithm::GetClosestNode(Node currentNode, vector<Node> visited) {
	bool depletedGraph = true;
	double lowestCost = DBL_MAX;
	Node res;
	Edge lowestEdge;
	for (auto edge : currentNode.edgeList) {
		if (edge.weight < lowestCost && !IsVisited(edge.dist, visited)) {
			lowestCost = edge.weight;
			lowestEdge = edge;
			depletedGraph = false;
		}
	}

	if (!depletedGraph)
		res = GetNodeFromID(lowestEdge.dist);
	else
		throw DepletedGraphException();

	return res;
}

bool BaseAlgorithm::IsVisited(int candidateNodeID, vector<Node> visited) {
	bool found = false;
	for (auto node : visited) {
		if (node.ID == candidateNodeID) {
			found = true;
		}
	}
	return found;
}

Node BaseAlgorithm::GetNodeFromID(int nodeID) {
	Node res;
	for (auto node : this->_graph.nodelist) {
		if (node.ID == nodeID) {
			res = node;
			break;
		}
	}
	return res;
}

void BaseAlgorithm::PathPrinter() {
	cout << "Number of POI: " << this->_path.size() - 2 << endl;
	for (auto node : this->_path) {
		std::cout << node.ID << " ---> ";
	}
}
