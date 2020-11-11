#include "baseAlgorithm.h"

/**
 * DFSAlgorithm class
 *
 * DFSAlgorithm class implements the second draft algorithm from the report.
 * It is a continuation of the first draft, but is able to find and compare
 * multiple routes in order to find the best route through DFS. A decision to
 * minimize the search down to 2 branches per node has been made. This decision
 * has been made as the ideal graphs that will be analyzed are completely dense.
 */
class DFSAlgorithm : public BaseAlgorithm {
  public:
	/**
	 * Parameterless function.
	 * Calculates the longest route given the graph and time interval assigned
	 * to the class instance. Given that the provided graph is fully dense, will
	 * always return a route that ends at the starting node.
	 */
	vector<Node> SecondDraft();

	/**
	 * Constructor for the DFSAlgorithm class.
	 * Time interval and graph must be provided.
	 */
	DFSAlgorithm(double timeInterval, Graph graph) {
		this->_timeInterval = timeInterval;
		this->_graph = graph;
	}

  private:
	/**
	 * This method returns the second closest node to the given node parameter.
	 *
	 * This method checks each edge from the edgelist of the node parameter.
	 * It then compares all the edges to find the respective lowest and second
	 * lowest edge weight. Finally it returns the ID from the second lowest edge
	 * using the GetNodeFromID() method in the baseAlgorithm class.
	 *
	 * @param currentPath Used to ensure that the next node is not in the
	 * current path that is being calculated.
	 * @param currentNode Reference node to find the second best distance from.
	 *
	 * @returns A node which has the second closest distance to the currentNode
	 * parameter.
	 */
	Node GetSecondBestNode(std::vector<Node> currentPath, Node *currentNode);
	/**
	 * This method returns the closest node to the given node parameter.
	 *
	 * This method checks each edge from the edgelist of the node parameter.
	 * It then compares all the edges to find the lowest edge weight.
	 * Finally it returns the ID from the lowest edge using the GetNodeFromID()
	 * method in the baseAlgorithm class.
	 *
	 * @param currentPath Used to ensure that the next node is not in the
	 * current path that is being calculated.
	 * @param currentNode Reference node to find the best distance from.
	 *
	 * @returns A node which has the closest distance to the currentNode
	 * parameter.
	 */
	Node GetClosestNode(std::vector<Node> currentPath, Node currentNode);
	/**
	 * This method checks whether the ID of the nextnode has already been
	 * visited in the current path. It checks all nodes in the current path
	 * vector and compares their ID to the nextNode integer.
	 *
	 * @param currentPath Used to ensure that the next node is not in the
	 * current path that is being calculated.
	 * @param nextNode Reference number representing the ID of the next node
	 * that is being compared by the currentPath parameter.
	 */
	bool IsInPath(std::vector<Node> currentPath, int nextNode);
};
