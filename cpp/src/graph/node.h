#ifndef NODE_H
#define NODE_H
#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

#include "edge.h"
class Node {
  public:
	Node() {}
	Node(int id) : ID(id) {} // Give node identifier
	int ID;                  // used as identifier
	bool firstReached = false;
	bool secondReached = false;
	bool childrensChecked = false; // used to identify a fully checked node in
								   // second draft algorithm.
	vector<Node> childrenNodes;

	void AddEdge(Edge e); // Add an edge to edgeList
	Edge GetEdge(int ID); // get an edge at index
	size_t GetEdgeListSize();
	std::vector<Edge> edgeList;

	// Used to compare edgelists of nodes
	bool EdgeListCompare(const Node &foo);

  private:
	// This is used to print the object in a nice way
	friend ostream &operator<<(ostream &out, const Node &n) {
		out << "ID: " << n.ID << setw(2);

		return out;
	};
};

#endif
