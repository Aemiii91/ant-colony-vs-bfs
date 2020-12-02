// std
#include <ctime>
#include <iostream>
#include <random>
#include <string>
// include
#include <termcolor/termcolor.hpp>
// submodules
#include "ownAlgorithm/DFSBranchLimitAlgorithm.h"
#include "ownAlgorithm/baseAlgorithm.h"
#include "ownAlgorithm/threeBranchAlgorithm.h"
#include <aco/AntColony.hpp>
#include <ownAlgorithm/depthFirstAlgorithm.h>
#include <ownAlgorithm/naiveAlgorithm.h>
#include <utils/ArgumentParser.hpp>
// local
#include "jsonparser.h"
#include <sstream>

int main(int argc, char **argv) {
	JsonParser parser;
	Graph graph = parser.ParseData(argv[1]);
	int k = std::stoi(argv[2]);
	int time = std::stoi(argv[3]);
	int start = std::stoi(argv[4]);
	DFSBranchLimitAlgorithm wow(30000,graph,time,start);
	vector<Node> reswow = wow.FourthDraft(k);
	vector<int> result;
	for(auto &iterator : reswow) {
		result.push_back(iterator.ID);
	}
	aco::Solution solution(wow._pathCost,result);
	std::cout << solution;
	return 0;
}
