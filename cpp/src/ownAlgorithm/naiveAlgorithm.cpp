#include "naiveAlgorithm.h"

vector<Node> NaiveAlgorithm::FirstDraftAlgo() {
	Node currentNode = this->_graph.nodelist.front();
	Node nextNode;
	this->_path.push_back(currentNode);

	while (this->_run) {
		try {
			nextNode = GetClosestNode(currentNode, this->_path);
		} catch (DepletedGraphException &e) {
			this->_run = false;
			std::cout << e.what() << std::endl;
			break;
		}
		if (CalculateConstraint(&nextNode)) {
			this->_path.push_back(nextNode);
			this->_timeSpent += TravelTime(&currentNode, &nextNode);
			currentNode = nextNode;
		} else {
			this->_run = false;
			std::cout << "naive algorithm has finished" << std::endl;
		}
	}
	BackTrackGraph();
	return this->_path;
}

bool NaiveAlgorithm::CalculateConstraint(Node *n2) {
	double travelCost = TravelTime(n2, &this->_path.front());
	return travelCost + this->_timeSpent < this->_timeInterval;
}

void NaiveAlgorithm::BackTrackGraph() {
	double travelTimeHome = 0;
	Node tempLast;
	for (auto node : this->_path) {
		travelTimeHome = TravelTime(&this->_path.back(), &this->_path.front());
		if (travelTimeHome + this->_timeSpent > this->_timeInterval) {
			tempLast = this->_path.back();
			this->_path.pop_back();
			this->_timeSpent -= TravelTime(&tempLast, &this->_path.back());
		}
	}
	this->_timeSpent += TravelTime(&this->_path.back(), &this->_path.front());
	std::cout << "cost of hometravel: "
			  << TravelTime(&this->_path.back(), &this->_path.front())
			  << std::endl;
	this->_path.push_back(this->_path.front());
	std::cout << "actual time spent: " << this->_timeSpent << std::endl;
}
