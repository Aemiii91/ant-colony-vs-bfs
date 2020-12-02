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
	DFSBranchLimitAlgorithm wow(30000,graph,time);
	vector<Node> reswow = wow.FourthDraft(k);
	wow.PathPrinter();
	std::cout << "kekw" << std::endl;
	return 0;
}
