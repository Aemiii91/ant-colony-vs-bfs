#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "graph/graph.h"

class JsonParser {
  public:
	/**
	 * Parses the data from the OpenRouteService API
	 * @param values file path to the json file
	 * @return returns a graph from the graph folder
	 */
	Graph ParseData(string jsonFilePath);
};
