#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

#include "graph.h"
void Graph::Print() {
	for (vector<int>::size_type i = 0; i < nodelist.size(); i++) {
		for (vector<int>::size_type k = 0; k < nodelist.at(i).GetEdgeListSize();
			 k++) {
			cout << nodelist.at(i) << " " << nodelist.at(i).GetEdge(k)
				 << setw(2);
		}
		cout << endl;
	}
}

void Graph::AddNode(Node n) {
	nodelist.emplace_back(n);
}

int Graph::GetGraphSize() {
	return this->nodelist.size();
}
