#pragma once

#include "graph/graph.h"
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <sstream>
#include <string>

class JsonParser {
  public:
	/**
	 * Parses the data from the OpenRouteService API
	 * @param values file path to the json file
	 * @return returns a graph from the graph folder
	 */
	Graph ParseData(string jsonFilePath);
};
