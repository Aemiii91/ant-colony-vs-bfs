#include "baseAlgorithm.h"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

class DFSBranchLimitAlgorithm : public BaseAlgorithm {
  public:
	vector<Node> FourthDraft(int branchLimit);

	DFSBranchLimitAlgorithm(double timeInterval, Graph graph, int timeAvailable, int startingPoint) {
		this->_timeInterval = timeInterval;
		this->_graph = graph;
		this->_timeAvailable = timeAvailable;
		this->_startingPoint = startingPoint;
	}
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
	int _timeAvailable;
	bool _canRunInTime(double timeSpent);
	int _startingPoint;
	Node _getNodeFromGraph(int id);
};
