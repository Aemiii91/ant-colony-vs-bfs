// std
#include <ctime>
#include <iostream>
#include <random>
// submodules
#include <aco/AntColony.hpp>
#include <utils/ArgumentParser.hpp>
#include <utils/printc.hpp>
// local
#include "jsonparser.h"
#include "ownAlgorithm/depthFirstAlgorithm.h"
#include "ownAlgorithm/naiveAlgorithm.h"

int main(int argc, char **argv) {
	utils::ArgumentParser args(argc, argv);

	// enable output colors
	printc::colorsEnabled(args.Exists("--colors"));

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
		printc::yellow("Not implemented.\n");
	} else {
		printc::red("Error: ");
		printc::bold("Subprogram not recognized.\n");
	}

	return 0;
}
