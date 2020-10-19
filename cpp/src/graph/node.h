#include <iostream>
#include <string>
#include <vector>

#include "edge.h"
using namespace std;
class Node {
public:
  Node(int id) : ID(id) {} // Give node identifier
  int ID; // used as identifier ( TODO: should be set to the same as POI)

  void addEdge(Edge e); // Add an edge to edgeList ( TODO Maybe initialize Edge
						// in the function for better error handling )
  Edge getEdge(int ID); // get an edge at index
						// ( TODO Mabye give edge an identifier);
  size_t getEdgeListSize();

private:
  // Made this private so you cant do edgeList.push_back
  vector<Edge> edgeList; // used to store edges the Node
  // This is used to print the object in a nice way
  friend ostream &operator<<(ostream &out, const Node &n) {
	out << "ID: " << n.ID << setw(2);

	return out;
  };
};
