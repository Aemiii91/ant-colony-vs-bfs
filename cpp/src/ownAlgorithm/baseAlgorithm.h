#pragma once
#include "../graph/graph.h"
#include <bits/stdc++.h>
#include <climits>
#include <exception>
#include <iostream>
#include <stdexcept>

/**
 * Base algorithm class, used as super class for other algorithms
 *
 * Contains standard functions used in "our own algorithm" that are nedded
 * regardless of which draft
 */
class BaseAlgorithm {
  public:
	BaseAlgorithm() {}
	/**
	 * Prints node ID's from path
	 *
	 * Essentially just prints the path in a human-readable way such as:
	 * Node1 --> Node2 --> Node_n
	 */
	void PathPrinter();

  protected:
	// functions
	/**
	 * Checks if a node is visited using the visited vector local to the class
	 *
	 * Iterates through all elements of this->vector<visited>.ID
	 * to check whether or not a node has already been visited
	 *
	 * @param candidateNodeID the ID of the node to be checked
	 * @return boolean if the node was found or not
	 */
	bool IsVisited(int candidateNodeID, vector<Node> visited);

	/**
	 * Returns the closest node in relation to the node given as param
	 *
	 * Iterates over the elements withing the edgeList of the node given
	 * as parameter. It also uses the IsVisited to ensure that it does not
	 * select a node that has already been visited.
	 *
	 * @param CurretNode the node to which the closest node must be found
	 * @return the closest node object
	 */
	Node GetClosestNode(Node CurrentNode, vector<Node> visited);
	/**
	 * Find node in graph.
	 *
	 * Small function to iterate over a graph object local to the class
	 * and return the node object corresponding to the ID given as param
	 *
	 * @param nodeID the ID of the node to be found
	 * @return node object
	 */
	Node GetNodeFromID(int nodeID);
	/**
	 * Calculates traveltime from n1 to n2
	 *
	 * iterates over the entire n1 edgelist to find the edge going from
	 * n1 to n2. When this is located the weight of the edge is saved
	 * and returned
	 *
	 * @param n1 pointer to the source node
	 * @param n2 pointer to the destination node
	 * @return the edge-weight between two nodes, corresponding to the
	 * traveltime.
	 */
	double TravelTime(Node *n1, Node *n2);
	// variables
	// the time constraint, given as parameter
	double _timeInterval;
	// the graph to be search, also given as parameter in constructor
	Graph _graph;
	// the resulting path which will be returned to the user
	std::vector<Node> _path;
};

/**
 * custom exception used to stop the algorithm in a natural way
 * in the case that the graph becomes depleted of new nodes
 * to visit.
 */
struct DepletedGraphException : public std::exception {
	const char *what() const throw() {
		return "Naive algorithm finished by a thrown DepletedGraphException";
	}
};
