#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

#include "graph.h"
void Graph::Print() {
  for (vector<int>::size_type i = 0; i < nodelist.size(); i++) {
	for (vector<int>::size_type k = 0; k < nodelist.at(i).GetEdgeListSize();
		 k++) {
	  cout << nodelist.at(i) << " " << nodelist.at(i).GetEdge(k) << setw(2);
	}
	cout << endl;
  }
}
// Cluster fuck just for fun PS its fast
void Graph::ImFastLetMeShowYou() {
  default_random_engine generator;
  normal_distribution<double> distribution(2.0, 0.2);
  int max_n = 10;
  clock_t start1 = clock();
  for (int i = 0; i < max_n; i++) {
	Node n(i);
	for (int k = 0; k < 5; k++) {
	  Edge e(n.ID, (rand() % 10), distribution(generator));
	  n.AddEdge(e);
	}
	AddNode(n);
  }
  Print();

  double duration = (std::clock() - start1) / (double)CLOCKS_PER_SEC;
  std::cout << "I'm fast!! " << duration << setw(20)
			<< "Number of nodes Add: " << max_n << '\n';
}
// Pushes a node to the list in this case the adjlist
void Graph::AddNode(Node n) {
  nodelist.emplace_back(n);
}

int Graph::GetGraphSize() {
  return this->nodelist.size();
}
