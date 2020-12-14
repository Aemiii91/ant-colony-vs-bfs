// std
#include <ctime>
#include <iostream>
#include <random>
// include
#include <argparse/argparse.hpp>
#include <termcolor/termcolor.hpp>
// submodules
#include <aco/AntColony.hpp>
#include <common/BaseAlgorithmRunner.hpp>
#include <ownAlgorithm/DFSBranchLimitAlgorithm.h>
#include <ownAlgorithm/baseAlgorithm.h>
#include <ownAlgorithm/depthFirstAlgorithm.h>
#include <ownAlgorithm/naiveAlgorithm.h>
#include <ownAlgorithm/threeBranchAlgorithm.h>
// local
#include "jsonparser.h"

int main(int argc, char **argv) {
	argparse::ArgumentParser args("routeplanner");
	JsonParser json;
	common::BaseAlgorithmRunner *algorithm;

	if (argc <= 1) {
		std::cout << "No subprogram specified." << std::endl;
		exit(0);
	}

	// first argument represents the name of a subprogram
	std::string subprogram = argv[1];

	if (subprogram == "aco") {
		aco::AntColony aco;
		algorithm = &aco;
		algorithm->AddArguments(&args);
	} else if (subprogram == "own") {
		// pass
	} else {
		std::cout << termcolor::red << "Error: " << termcolor::reset;
		std::cout << "Subprogram not recognized." << std::endl;
		exit(0);
	}

	args.add_argument("subprogram").default_value("aco");
	args.add_argument("--colors").default_value(false).implicit_value(true);
	args.add_argument("--data").default_value(std::string{"berlin.json"});
	args.add_argument("--cost").default_value(algorithm->costConstraint);
	args.add_argument("--start").default_value(algorithm->startVertex);
	args.add_argument("--iterations").default_value(algorithm->iterationLimit);

	try {
		args.parse_args(argc, argv);
	} catch (const std::runtime_error &err) {
		std::cout << err.what() << std::endl;
		std::cout << args;
		exit(0);
	}

	// enable/disable output colors
	termcolor::setEnabled(args.get<bool>("--colors"));

	// default dataset path
	std::string dataPath = args.get<std::string>("--data");

	algorithm->graph = json.ParseData(dataPath);
	algorithm->costConstraint = args.get<int>("--cost");
	algorithm->startVertex = args.get<int>("--start");
	algorithm->iterationLimit = args.get<int>("--iterations");

	if (subprogram == "aco") {
		algorithm->Run(&args);
	} else if (subprogram == "own") {
		// load the graph
		Graph graph = json.ParseData(dataPath);

		// run own algorithms
		DFSAlgorithm Alg(algorithm->costConstraint, algorithm->graph);
		vector<Node> resAlg = Alg.SecondDraft();

		NaiveAlgorithm Naive(algorithm->costConstraint, algorithm->graph);
		vector<Node> resNaive = Naive.FirstDraftAlgo();

		ThreeBranchAlgorithm Three(algorithm->costConstraint, algorithm->graph);
		vector<Node> resThree = Three.ThirdDraft();

		DFSBranchLimitAlgorithm Four(algorithm->costConstraint,
									 algorithm->graph);
		vector<Node> resFour = Four.FourthDraft(3);

		cout << endl;
		cout << endl;

		cout << "Interval: " << algorithm->costConstraint << endl;
		cout << "Dataset: " << dataPath << endl;
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
	}

	return 0;
}
