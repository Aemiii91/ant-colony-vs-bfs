#include "threeBranchAlgorithm.h"
#include <iostream>

vector<Node> ThreeBranchAlgorithm::ThirdDraft() {
	vector<Node> currentPath, bestPath;
	vector<double> currentTime, bestTime;
	bool travel = true;
	int iteratorCount = 0;
	int bestCount;
	double timeSpent = 0;

	// Prerequisite variable assignment
	Node root = this->_graph.nodelist.front();
	Node currentNode = root;
	currentPath.emplace_back(root);
	currentTime.emplace_back(0);
	Node nextNode = GetClosestNode(currentPath, currentNode);
	Node secondNode = GetSecondBestNode(currentPath, currentNode);
	Node thirdNode = GetThirdBestNode(currentPath, currentNode);

	while (travel) {
		nextNode = GetClosestNode(currentPath, currentNode);
		while (TravelTime(&currentNode, &nextNode) +
					   TravelTime(&nextNode, &root) + timeSpent <=
				   this->_timeInterval &&
			   currentNode.firstReached == false &&
			   nextNode.edgeList.size() >= 1) {
			currentTime.emplace_back(TravelTime(&currentNode, &nextNode) +
									 timeSpent);
			timeSpent = currentTime.back();

			currentPath.pop_back();
			currentNode.firstReached = true;
			currentPath.emplace_back(currentNode);

			currentNode = GetClosestNode(currentPath, currentNode);
			currentPath.emplace_back(currentNode);
			nextNode = GetClosestNode(currentPath, currentNode);
		}
		if (currentPath.size() > bestPath.size()) {
			bestPath = currentPath;
			bestTime = currentTime;
			cout << "Better path found at iteration: " << iteratorCount << endl;
			bestCount = iteratorCount;
		}

		secondNode = GetSecondBestNode(currentPath, currentNode);
		while (true) {
			if (currentNode.secondReached == true) {
				break;
			}
			while (secondNode.GetEdgeListSize() < 1) {
				currentPath.pop_back();
				currentNode = currentPath.back();
				currentTime.pop_back();
				timeSpent = currentTime.back();
				secondNode = GetSecondBestNode(currentPath, currentNode);
			}
			while (TravelTime(&currentNode, &secondNode) +
						   TravelTime(&secondNode, &root) + timeSpent >
					   this->_timeInterval &&
				   currentNode.secondReached == false) {
				currentPath.pop_back();
				currentNode = currentPath.back();
				currentTime.pop_back();
				timeSpent = currentTime.back();
				secondNode = GetSecondBestNode(currentPath, currentNode);
			}
			if (TravelTime(&currentNode, &secondNode) +
						TravelTime(&secondNode, &root) + timeSpent <=
					this->_timeInterval &&
				currentNode.secondReached == false &&
				secondNode.edgeList.size() >= 1) {

				currentPath.pop_back();
				currentNode.secondReached = true;
				currentPath.emplace_back(currentNode);

				currentTime.emplace_back(TravelTime(&currentNode, &secondNode) +
										 timeSpent);

				timeSpent = currentTime.back();
				currentNode = GetSecondBestNode(currentPath, currentNode);
				currentPath.emplace_back(currentNode);
				nextNode = GetClosestNode(currentPath, currentNode);
				secondNode = GetSecondBestNode(currentPath, currentNode);
			}

			while (TravelTime(&currentNode, &nextNode) +
						   TravelTime(&nextNode, &root) + timeSpent <=
					   this->_timeInterval &&
				   currentNode.firstReached == false &&
				   nextNode.edgeList.size() >= 1) {
				currentTime.emplace_back(TravelTime(&currentNode, &nextNode) +
										 timeSpent);
				timeSpent = currentTime.back();

				currentPath.pop_back();
				currentNode.firstReached = true;
				currentPath.emplace_back(currentNode);

				currentNode = GetClosestNode(currentPath, currentNode);
				currentPath.emplace_back(currentNode);
				nextNode = GetClosestNode(currentPath, currentNode);
			}
			if (currentPath.size() > bestPath.size()) {
				bestPath = currentPath;
				bestTime = currentTime;
				cout << "Better path found at iteration: " << iteratorCount
					 << endl;
				bestCount = iteratorCount;
			}
		}

		thirdNode = GetThirdBestNode(currentPath, currentNode);
		if (TravelTime(&currentNode, &thirdNode) +
					TravelTime(&thirdNode, &root) + timeSpent <=
				this->_timeInterval &&
			currentNode.childrensChecked == false &&
			thirdNode.edgeList.size() >= 1) {

			currentPath.pop_back();
			currentNode.childrensChecked = true;
			currentPath.emplace_back(currentNode);

			currentTime.emplace_back(TravelTime(&currentNode, &thirdNode) +
									 timeSpent);

			timeSpent = currentTime.back();
			currentNode = GetThirdBestNode(currentPath, currentNode);
			currentPath.emplace_back(currentNode);
			nextNode = GetClosestNode(currentPath, currentNode);
		} else {
			if (currentNode.ID != root.ID) {
				currentPath.pop_back();
				currentNode = currentPath.back();
				currentTime.pop_back();
				timeSpent = currentTime.back();
			}
		}

		if (currentNode.ID == root.ID && currentNode.childrensChecked == true) {
			travel = false;
		}
		if (iteratorCount == 1500) {
			travel = false;
		}
		if (!travel) {
			break;
		}

		iteratorCount++;
		cout << "Count: " << iteratorCount << endl;
	}

	bestTime.emplace_back(TravelTime(&bestPath.front(), &bestPath.back()) +
						  bestTime.back());
	bestPath.emplace_back(root);
	this->_path = bestPath;
	cout << "TBS Path cost: " << bestTime.back() << endl;
	cout << "Best route found at iteration: " << bestCount << endl;
	return this->_path;
}

bool ThreeBranchAlgorithm::IsInPath(std::vector<Node> currentPath,
									int nextNode) {
	for (auto Node : currentPath) {
		if (nextNode == Node.ID) {
			return true;
		}
	}
	return false;
}

Node ThreeBranchAlgorithm::GetClosestNode(vector<Node> currentPath,
										  Node currentNode) {
	double lowestCost;
	Node res;
	Edge lowestEdge;
	vector<Edge> sortedPath = currentNode.edgeList;
	sort(sortedPath.begin(), sortedPath.end(),
		 [](const Edge &e1, const Edge &e2) -> bool {
			 return e1.weight < e2.weight;
		 });
	for (Edge edge : sortedPath) {
		if (!IsInPath(currentPath, edge.dist)) {
			lowestEdge = edge;
			break;
		}
	}
	res = GetNodeFromID(lowestEdge.dist);
	return res;
}

Node ThreeBranchAlgorithm::GetSecondBestNode(std::vector<Node> currentPath,
											 Node currentNode) {
	Edge lowestEdge;
	Edge secondLowestEdge;
	Node res;
	vector<Edge> sortedPath = currentNode.edgeList;
	sort(sortedPath.begin(), sortedPath.end(),
		 [](const Edge &e1, const Edge &e2) -> bool {
			 return e1.weight < e2.weight;
		 });

	for (Edge edge : sortedPath) {
		if (!IsInPath(currentPath, edge.dist)) {
			lowestEdge = edge;
			break;
		}
	}
	for (Edge edge : sortedPath) {
		if (!IsInPath(currentPath, edge.dist) &&
			edge.weight > lowestEdge.weight) {
			secondLowestEdge = edge;
			break;
		}
	}
	res = GetNodeFromID(secondLowestEdge.dist);
	return res;
}

Node ThreeBranchAlgorithm::GetThirdBestNode(std::vector<Node> currentPath,
											Node currentNode) {
	Edge lowestEdge;
	Edge secondLowestEdge;
	Edge thirdLowestEdge;
	Node res;
	vector<Edge> sortedPath = currentNode.edgeList;
	sort(sortedPath.begin(), sortedPath.end(),
		 [](const Edge &e1, const Edge &e2) -> bool {
			 return e1.weight < e2.weight;
		 });

	for (Edge edge : sortedPath) {
		if (!IsInPath(currentPath, edge.dist)) {
			lowestEdge = edge;
			break;
		}
	}
	for (Edge edge : sortedPath) {
		if (!IsInPath(currentPath, edge.dist) &&
			edge.weight > lowestEdge.weight) {
			secondLowestEdge = edge;
			break;
		}
	}
	for (Edge edge : sortedPath) {
		if (!IsInPath(currentPath, edge.dist) &&
			edge.weight > secondLowestEdge.weight) {
			thirdLowestEdge = edge;
			break;
		}
	}
	res = GetNodeFromID(thirdLowestEdge.dist);
	return res;
}
