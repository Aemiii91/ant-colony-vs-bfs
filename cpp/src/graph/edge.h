#include <iomanip>
#include <iostream>

using namespace std;
class Edge {
 public:
  Edge(int s, int d, double w) : scr(s), dist(d) {}
  int scr;        // Used as the ID and the source node
  double weight;  // Used as weight
  int dist;       // The destination of the edge

 private:
  // This is used to print the object in a nice way
  friend ostream &operator<<(ostream &out, const Edge &e) {
    cout << "----> " << setw(2) << e.dist << setw(2) << "  Cost: " << e.weight;

    return out;
  }
};
