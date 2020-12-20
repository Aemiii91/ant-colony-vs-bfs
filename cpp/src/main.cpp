// std
#include <ctime>
#include <iostream>
#include <random>
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

int main(int argc, char **argv) {
	JsonParser parser;
	Graph graph;

	utils::ArgumentParser args(argc, argv);

	// enable/disable output colors
	termcolor::setEnabled(args.Exists("--colors"));

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
		args.Get("--cost",&interval);
		args.Get("-k",&kLimit);
		DFSBranchLimitAlgorithm Four(interval, graph);
		vector<Node> resFour = Four.FourthDraft(kLimit);
		cout << "DFSBranchLimitAlgorithm: RESULTS" << endl;
		Four.PathPrinter();
		cout << endl;
	}else {
		std::cout << termcolor::red << "Error: " << termcolor::reset;
		std::cout << "Subprogram not recognized." << std::endl;
	}

	return 0;
}
