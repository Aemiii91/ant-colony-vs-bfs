#include "baseAlgorithm.h"

/**
 * NaiveAlgoritm class
 *
 * Essemtially, this class implements the first draft algorithm from our report
 * Whether or not this class will be changed to contain the second draft Is
 * Not certain, but I highly doubt it
 */
class NaiveAlgorithm : public BaseAlgorithm {
  public:
	NaiveAlgorithm(double timeInterval, Graph graph) {
		this->_timeInterval = timeInterval;
		this->_graph = graph;
	}
	/**
	 * Runner function for the firstDraftAlgorithm
	 *
	 * Is parameterless, but depends on the graph provided in class
	 */
	vector<Node> FirstDraftAlgo();

  private:
	/**
	 * Check constraint
	 *
	 * Checks if the algorithm can still make it back to the starting point
	 * by checking the accumulated timeSpent and the distance between the node
	 * given as parameter and and the cost of going to the startnode
	 * This is the only function that is not inherited from the BaseAlgorithm
	 * class, since it is specific to the algorithm itself.
	 *
	 * @param n2 pointer to the candidate node
	 *
	 * @return true if the constraint can be satisfied, false if not
	 */
	bool CalculateConstraint(Node *n2);
	bool _run = true;
	/**
	 * Small method to go backwards in the graph, checking the constraint
	 *
	 * Uses the accumulated timespent and holds it against the traveltime
	 * From the current final node of the path to the starting node
	 * If the cost of going from the final node exceeds the time constraint
	 * the final node is removed from the path. This process continues untill
	 * we can get back to the starting node from the final node within the
	 * given constraint
	 */
	void BackTrackGraph();
	/// had to move this variable here in order to backtrack the graph later
	double _timeSpent = 0;
};
