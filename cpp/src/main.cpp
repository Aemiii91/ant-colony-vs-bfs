//#include "jsonparser.h"
#include <ctime>
#include <iostream>
#include <random>

//#include "utils/ArgumentParser.hpp"
#include "aco/run.hpp"
#include "jsonparser.h"

int main(int argc, char **argv) {
	utils::ArgumentParser args(argc, argv);

	JsonParser parser;
	Graph graph = parser.ParseData(args.Get<std::string>("--data",
		"../data/matrix500.json"));

	if (argc <= 1) {
		std::cout << "No subprogram specified." << std::endl;
		return 0;
	}

	std::string subprogram = argv[1];

	if (subprogram == "aco") {
		aco::run(&graph, &args);
	}
	else {
		std::cout << "Subprogram not recognized." << std::endl;
	}

	return 0;
}
