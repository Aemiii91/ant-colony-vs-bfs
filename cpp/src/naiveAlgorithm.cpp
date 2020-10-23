#include "naiveAlgorithm.h"

vector<Node> NaiveAlgorithm::FirstDraftAlgo() {
  Node currentNode = this->_graph.nodelist.front(); // nextNode = g.nodelist[0];
  Node nextNode;
  int POI = 0;
  double timeSpent = 0;
  this->_path.push_back(currentNode);
  this->_visited.push_back(currentNode);

  while (this->_run) {
	try {
	  nextNode = GetClosestNode(currentNode);
	} catch (DepletedGraphException &e) {
	  this->_run = false;
	  std::cout << e.what() << std::endl;
	  break;
	}
	if (CalculateConstraint(&nextNode, timeSpent)) {
	  POI++;
	  this->_path.push_back(nextNode);
	  this->_visited.push_back(nextNode);
	  timeSpent += TravelTime(&currentNode, &nextNode);
	  currentNode = nextNode;
	} else {
	  this->_run = false;
	  std::cout << "naive algorithm has finished" << std::endl;
	}
  }
  this->_path.push_back(this->_path.front());
  cout << "Number of POI: " << POI << endl;
  return this->_path;
}

bool NaiveAlgorithm::CalculateConstraint(Node *n2, double timeSpent) {
  Node startNode = this->_path.front();
  double travelCost = TravelTime(n2, &startNode);
  return travelCost + timeSpent < this->_timeInterval;
}
