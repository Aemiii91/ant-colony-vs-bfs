#include "baseAlgorithm.h"

class DFSBranchLimitAlgorithm : public BaseAlgorithm {
  public:
	vector<Node> FourthDraft(int branchLimit);

	DFSBranchLimitAlgorithm(double timeInterval, Graph graph) {
		this->_timeInterval = timeInterval;
		this->_graph = graph;
	}

  private:
	vector<Node> GenerateChildren(Node currentNode, vector<Node> currentPath,
								  int branchLimit);
	bool IsInPath(vector<Node> currentPath, int nextNode);
	// 	Node GetClosestNode(std::vector<Node> currentPath, Node currentNode);
	// 	Node GetSecondBestNode(std::vector<Node> currentPath, Node currentNode);
	// 	Node GetThirdBestNode(std::vector<Node> currentPath, Node currentNode);
	// 	bool IsInPath(std::vector<Node> currentPath, int nextNode);
};
