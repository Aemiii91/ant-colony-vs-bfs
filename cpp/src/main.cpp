// std
#include <ctime>
#include <iostream>
#include <random>
// include
#include <termcolor/termcolor.hpp>
// submodules
#include <aco/AntColony.hpp>
#include <ownAlgorithm/depthFirstAlgorithm.h>
#include <ownAlgorithm/naiveAlgorithm.h>
#include <utils/ArgumentParser.hpp>
// local
#include "jsonparser.h"

int main(int argc, char **argv) {
	utils::ArgumentParser args(argc, argv);

	// enable/disable output colors
	termcolor::setEnabled(args.Exists("--colors"));

	// default dataset path
	std::string path = "../data/matrix500.json";
	// get inputted dataset path
	args.Get("--data", &path);

	// load the graph
	JsonParser parser;
	Graph graph = parser.ParseData(path);

	if (argc <= 1) {
		std::cout << "No subprogram specified." << std::endl;
		return 0;
	}

	// first argument represents the name of a subprogram
	std::string subprogram = argv[1];

	if (subprogram == "aco") {
		aco::AntColony::run(&graph, &args);
	} else if (subprogram == "naive") {
		// run naive algorithm
		std::cout << "Not implemented." << std::endl;
	} else {
		std::cout << termcolor::red << "Error: " << termcolor::reset;
		std::cout << "Subprogram not recognized." << std::endl;
	}

	return 0;
}
