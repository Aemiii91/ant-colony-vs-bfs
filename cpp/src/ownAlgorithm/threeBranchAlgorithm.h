#include "baseAlgorithm.h"

class ThreeBranchAlgorithm : public BaseAlgorithm {
  public:
	vector<Node> ThirdDraft();

	ThreeBranchAlgorithm(double timeInterval, Graph graph) {
		this->_timeInterval = timeInterval;
		this->_graph = graph;
	}

  private:
	Node GetClosestNode(std::vector<Node> currentPath, Node currentNode);
	Node GetSecondBestNode(std::vector<Node> currentPath, Node currentNode);
	Node GetThirdBestNode(std::vector<Node> currentPath, Node currentNode);
	bool IsInPath(std::vector<Node> currentPath, int nextNode);
};
