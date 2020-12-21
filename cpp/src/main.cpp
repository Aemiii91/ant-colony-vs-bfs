// std
#include <ctime>
#include <iostream>
#include <string>
// include
#include <termcolor/termcolor.hpp>
// submodules
#include "ownAlgorithm/DFSBranchLimitAlgorithm.h"
#include <aco/AntColony.hpp>
#include <utils/ArgumentParser.hpp>
// local
#include "jsonparser.h"
#include <sstream>

int main(int argc, char **argv) {
	JsonParser parser;
	Graph graph;

	utils::ArgumentParser args(argc, argv);

	// default dataset path
	std::string path = "berlin.json";
	// get inputted dataset path
	args.Get("--data", &path);

	// load the graph
	graph = parser.ParseData(path);

	if (argc <= 1) {
		std::cout << "No subprogram specified." << std::endl;
		return 0;
	}

	// first argument represents the name of a subprogram
	std::string subprogram = argv[1];

	if (subprogram == "aco") {
		aco::AntColony::run(&graph, &args);

	} else if (subprogram == "kdfs") {
		int interval = 30000;
		int kLimit = 1;
		int runtimeLimit = 30000;
		int startingPoint = 0;
		args.Get("--cost", &interval);
		args.Get("-k", &kLimit);
		args.Get("--time", &runtimeLimit);
		args.Get("--start", &startingPoint);
		DFSBranchLimitAlgorithm kdfs(interval, graph, runtimeLimit,
									 startingPoint);
		vector<Node> result = kdfs.FourthDraft(kLimit);
		kdfs.PathPrinter();
		std::cout << termcolor::bold << termcolor::green;
		std::cout << "Done." << termcolor::reset << std::endl;
	} else {
		std::cout << termcolor::red << "Error: " << termcolor::reset;
		std::cout << "Subprogram not recognized." << std::endl;
	}

	return 0;
}
