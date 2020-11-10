#include "baseAlgorithm.h"

double BaseAlgorithm::TravelTime(Node *n1, Node *n2) {
	double cost = 0.0;
	for (auto iterator : n1->edgeList) {
		if (iterator.dist == n2->ID) {
			cost = iterator.weight;
		}
	}
	return cost;
}

Node BaseAlgorithm::GetClosestNode(Node currentNode) {
	bool depletedGraph = true;
	double lowestCost = LONG_MAX;
	Node res;
	Edge lowestEdge;
	for (auto iterator : currentNode.edgeList) {
		if (iterator.weight < lowestCost && !IsVisited(iterator.dist)) {
			lowestCost = iterator.weight;
			lowestEdge = iterator;
			depletedGraph = false;
		}
	}

	if (!depletedGraph)
		res = GetNodeFromID(lowestEdge.dist);
	else
		throw DepletedGraphException();

	return res;
}

bool BaseAlgorithm::IsVisited(int candidateNodeID) {
	bool found = false;
	for (auto iterator : this->_visited) {
		if (iterator.ID == candidateNodeID) {
			found = true;
		}
	}
	return found;
}

Node BaseAlgorithm::GetNodeFromID(int nodeID) {
	Node res;
	for (auto iterator : _graph.nodelist) {
		if (iterator.ID == nodeID) {
			res = iterator;
		}
	}
	return res;
}

void BaseAlgorithm::PathPrinter() {
	for (auto iterator : this->_path) {
		std::cout << iterator.ID << " ---> ";
	}
}