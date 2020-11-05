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
	int ID; // used as identifier ( TODO: should be set to the same as POI)

	void AddEdge(Edge e); // Add an edge to edgeList ( TODO Maybe initialize
						  // Edge in the function for better error handling )
	Edge GetEdge(int ID); // get an edge at index
						  // ( TODO Mabye give edge an identifier);
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
