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
	Graph graph = parser.ParseData("berlin.json");
	int interval = 30000;

	DFSAlgorithm Alg(interval, graph);
	vector<Node> resAlg = Alg.SecondDraft();

	NaiveAlgorithm Naive(interval, graph);
	vector<Node> resNaive = Naive.FirstDraftAlgo();

	ThreeBranchAlgorithm Three(interval, graph);
	vector<Node> resThree = Three.ThirdDraft();

	DFSBranchLimitAlgorithm Four(interval, graph);
	vector<Node> resFour = Four.FourthDraft(3);
	cout << endl;
	cout << endl;

	cout << "Interval: " << interval << endl;
	cout << "Graph: matrix500.json" << endl;
	cout << endl;

	cout << "NaiveAlgorithm: RESULTS" << endl;
	Naive.PathPrinter();
	cout << endl;

	cout << "DFSAlgorithm: RESULTS" << endl;
	Alg.PathPrinter();
	cout << endl;

	cout << "ThreeBranchAlgorithm: RESULTS" << endl;
	Three.PathPrinter();
	cout << endl;

	cout << "DFSBranchLimitAlgorithm: RESULTS" << endl;
	Four.PathPrinter();
	cout << endl;

	utils::ArgumentParser args(argc, argv);

	// enable/disable output colors
	termcolor::setEnabled(args.Exists("--colors"));

	// default dataset path
	std::string path = "../data/matrix500.json";
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
	} else if (subprogram == "naive") {
		// run naive algorithm
		std::cout << "Not implemented." << std::endl;
	} else {
		std::cout << termcolor::red << "Error: " << termcolor::reset;
		std::cout << "Subprogram not recognized." << std::endl;
	}

	return 0;
}
