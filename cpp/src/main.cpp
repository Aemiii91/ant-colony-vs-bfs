//#include "jsonparser.h"
#include <ctime>
#include <iostream>
#include <random>

#include "aco/Colony.hpp"
#include "jsonparser.h"

using namespace std;
int main(int argc, char **argv) {
	time_t t;
	srand(time(&t));

	JsonParser parser;

	std::cout << "Loading graph..." << std::endl;
	Graph graph = parser.ParseData("../data/matrix500.json");

	std::cout << "Spawning colony..." << std::endl;
	aco::Colony colony(&graph);

    colony.costConstraint = 30000;
    colony.returnHome = true;
    colony.evaporation = 0.4;
    colony.antCount = 750;
    colony.iterations = 100;

	std::cout << "Solving..." << std::endl;
	aco::Solution best = colony.Solve();

    colony.PrintSolution(best);

	return 0;
}
