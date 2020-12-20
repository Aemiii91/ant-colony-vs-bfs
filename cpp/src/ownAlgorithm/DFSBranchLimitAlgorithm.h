#include "baseAlgorithm.h"
/**
 * DFSBranchLimitAlgorithm class for the K-DFS algorithm implementation.
 */
class DFSBranchLimitAlgorithm : public BaseAlgorithm {
  public:
	/**
	 * Calculates the longest route given the branchLimit parameter and the
	 * graph and time interval assigned to the class instance. Given that the
	 * provided graph is fully dense, will always return a route that ends at
	 * the starting node.
	 *
	 * @param branchLimit Used to limit the amount of branches per node.
	 * @returns A vector containing the best computed route through the graph
	 * with the given initializations and parameters.
	 */
	vector<Node> FourthDraft(int branchLimit);

	/**
	 * Constructor for the DFSBranchLimitAlgorithm class.
	 * Time interval and graph must be provided.
	 *
	 * @param timeInterval Used to initialize the time interval given in
	 * seconds.
	 * @param graph Used to initialize the dataset.
	 */
	DFSBranchLimitAlgorithm(double timeInterval, Graph graph) {
		this->_timeInterval = timeInterval;
		this->_graph = graph;
	}

  private:
	/**
	 *This method generates the k amount of branches to be visited for a node.
	 *
	 * @param currentNode Used to specify the node to be checked.
	 * @param currentPath Used to check if the generated branching nodes already
	 *exist in the current path of the iteration.
	 * @param branchLimit Used to limit the amount of branches per node.
	 *
	 * @returns A vector containing the branching nodes for the given
	 *currentNode parameter.
	 */
	vector<Node> GenerateChildren(Node currentNode, vector<Node> currentPath,
								  int branchLimit);

	/**
	 * Used to check if a node is in the path.
	 * @param currentPath Current path to be checked.
	 * @param nextNode ID on the checked node.
	 *
	 * @returns True or False depending on whether the node exists in the
	 * currentPath parameter or not.
	 */
	bool IsInPath(vector<Node> currentPath, int nextNode);
};
