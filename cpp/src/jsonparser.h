#include "graph/graph.h"
#include "rapidjson.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class JsonParser {
public:
  Graph ParseData(string json);
};
