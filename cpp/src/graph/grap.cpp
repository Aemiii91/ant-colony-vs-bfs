#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

#include "graph.h"
void Graph::print() {
  for (vector<int>::size_type i = 0; i < nodelist.size(); i++) {
    for (vector<int>::size_type k = 0; k < nodelist.at(i).edgeList.size();
         k++) {
      cout << nodelist.at(i) << " " << nodelist.at(i).edgeList.at(k) << setw(2);
    }
    cout << endl;
  }
}
// Cluster fuck just for fun PS its fast
void Graph::ImFastLetMeShowYou() {
  default_random_engine generator;
  normal_distribution<double> distribution(1.0, 2.0);
  int max_n = 10;
  clock_t start1 = clock();
  for (int i = 0; i < max_n; i++) {
    Node n(i);
    addNode(n);
    for (int k = 0; k < 5; k++) {
      Edge e(1.2, (rand() % 10));
      direcAddEdge(n, e);
    }
  }
  print();
  double duration = (std::clock() - start1) / (double)CLOCKS_PER_SEC;
  std::cout << "I'm fast!! " << duration << setw(20)
            << "Number of nodes Add: " << max_n << '\n';
}
// Pushes a node to the list in this case the adjlist
void Graph::addNode(Node n) { nodelist.push_back(n); }
// Don't know if this works!
void Graph::biAddEdge(Node n, Edge e, Node s) {
  nodelist.at(n.ID).edgeList.push_back(e);
  nodelist.at(s.ID).edgeList.push_back(e);
}
// Pushes Edge object to the Node::edgeList give sourer give a Node
void Graph::direcAddEdge(Node n, Edge e) {
  nodelist.at(n.ID).edgeList.push_back(e);
}
