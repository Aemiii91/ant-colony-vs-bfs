#include "jsonparser.h"

using namespace rapidjson;
using namespace std;

Graph JsonParser::ParseData(string jsonFilePath) {
  Document document;
  Graph graph;
  std::ifstream jsonData(jsonFilePath);
  stringstream buffer;
  buffer << jsonData.rdbuf();

  string stringJson = buffer.str();

  document.Parse(stringJson.c_str());

  // Gets the size of the durations object in the json
  SizeType outerSize = document["durations"].Size();
  for (SizeType i = 0; i < outerSize; ++i) {
	Node node(i);
	// Gets the size of one of the arrays inside the durations object
	SizeType innerSize = document["durations"][i].Size();
	for (SizeType j = 0; j < innerSize; ++j) {
	  double duration = document["durations"][i][j].GetDouble();
	  if (duration != 0) {
		// Add edge from current node, to the index of the loop and add duration
		// as the cost.
		Edge e(node.ID, j, duration);
		node.AddEdge(e);
	  }
	}

	graph.AddNode(node);
  }

  return graph;
}
