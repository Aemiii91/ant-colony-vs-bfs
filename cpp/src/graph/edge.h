#ifndef EDGE_H
#define EDGE_H
#pragma once

#include <iomanip>
#include <iostream>

using namespace std;
class Edge {
  public:
	Edge() {}
	Edge(int s, int d, double w) : scr(s), dist(d), weight(w) {}
	int scr;       // Used as the ID and the source node
	int dist;      // The destination of the edge
	double weight; // Used as weight

	// Operator override for comparing equal edges
	bool operator==(const Edge &foo);
	// Operator override for comparing not equal edges
	bool operator!=(const Edge &foo);

  private:
	// This is used to print the object in a nice way
	friend ostream &operator<<(ostream &out, const Edge &e) {
		out << "----> " << setw(1) << e.dist << setw(1)
			<< "  Cost: " << e.weight;
		return out;
	}
};

#endif
