// clang-format off
#include "DFSBranchLimitAlgorithm.h"
#include <iostream>
#define CANTRAVELHOME TravelTime(&currentNode, &nextNode) +\
	TravelTime(&nextNode, &root) + timeSpent <= \
	this->_timeInterval && \
	nextNode.GetEdgeListSize() >= 1 && \
	currentNode.childrenNodes.size() >= 1

vector<Node> DFSBranchLimitAlgorithm::FourthDraft(int branchLimit) {
	Node nextNode;
	vector<Node> currentPath, bestPath;
	vector<double> currentTime, bestTime;

	bool travel = true;
	int iteratorCount = 0;
	int bestCount;
	double timeSpent = 0;

	Node root = this->_graph.nodelist.front();
	Node currentNode = root;
	currentPath.emplace_back(root);

	currentNode.childrenNodes =
		GenerateChildren(currentNode, currentPath, branchLimit);
	currentPath.pop_back();
	currentPath.emplace_back(currentNode);

	nextNode = currentNode.childrenNodes[0];
	currentTime.emplace_back(0);

	while (travel) {

		while (CANTRAVELHOME) {
			currentTime.emplace_back(TravelTime(&currentNode, &nextNode) +
									 timeSpent);
			timeSpent = currentTime.back();

			currentPath.pop_back();
			currentNode.childrenNodes.erase(currentNode.childrenNodes.begin());
			currentPath.emplace_back(currentNode);
			if (currentNode.childrenNodes.size() == 0) {
				currentPath.pop_back();
				currentNode.childrensChecked = true;
				currentPath.emplace_back(currentNode);
			}
	
			currentNode = nextNode;
			currentNode.childrenNodes =
				GenerateChildren(currentNode, currentPath, branchLimit);
			currentPath.emplace_back(currentNode);

			if (currentNode.childrenNodes.size() >= 1) {
				nextNode = currentNode.childrenNodes[0];
			}

			if (currentPath.size() > bestPath.size() ||
					(currentPath.size() == bestPath.size() &&
					 currentTime.back() < bestTime.back())) {
				bestPath = currentPath;
				bestTime = currentTime;
				bestCount = iteratorCount;
			}
			
		}

		currentNode.childrenNodes.clear();
		currentNode.childrensChecked = true;

		while (currentNode.childrensChecked == true
				&& currentNode.ID != root.ID) {
			currentPath.pop_back();
			currentNode = currentPath.back();

			if (currentNode.childrenNodes.size() >= 1) {
				nextNode = currentNode.childrenNodes[0];
			}

			currentTime.pop_back();
			timeSpent = currentTime.back();
		}

		if (currentNode.ID == root.ID
			&& currentNode.childrensChecked == true || iteratorCount == 20000) {
			travel = false;
			break;
		}

		iteratorCount++;
	}
	bestTime.emplace_back(TravelTime(&bestPath.front(), &bestPath.back()) +
						  bestTime.back());
	bestPath.emplace_back(root);
	this->_path = bestPath;
	return this->_path;
}

vector<Node> DFSBranchLimitAlgorithm::GenerateChildren(Node currentNode,
													   vector<Node> currentPath,
													   int branchLimit) {
	vector<Edge> sortedPath = currentNode.edgeList;
	vector<Node> children;
	sort(sortedPath.begin(), sortedPath.end(),
		 [](const Edge &e1, const Edge &e2) -> bool {
			 return e1.weight < e2.weight;
		 });
	int limit = branchLimit;

	for (int i = 0; i < limit; i++) {
		if (sortedPath.size() > i) {
			if (!IsInPath(currentPath, sortedPath[i].dist)) {
				children.emplace_back(GetNodeFromID(sortedPath[i].dist));
			} else {
				limit++;
			}
		}
	}
	return children;
}

bool DFSBranchLimitAlgorithm::IsInPath(std::vector<Node> currentPath,
									   int nextNode) {
	for (auto Node : currentPath) {
		if (nextNode == Node.ID) {
			return true;
		}
	}
	return false;
}
// clang-format on
