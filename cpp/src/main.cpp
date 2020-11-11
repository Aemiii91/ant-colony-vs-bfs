#include "jsonparser.h"
#include "ownAlgorithm/baseAlgorithm.h"
#include "ownAlgorithm/depthFirstAlgorithm.h"
#include "ownAlgorithm/naiveAlgorithm.h"
#include <ctime>
#include <iostream>
#include <random>

using namespace std;

int main(int argc, char **argv) {
	JsonParser parser;
	Graph graph = parser.ParseData("matrix500.json");
	int interval = 50000;

	DFSAlgorithm Alg(interval, graph);
	vector<Node> resAlg = Alg.SecondDraft();

	NaiveAlgorithm Naive(interval, graph);
	vector<Node> resNaive = Naive.FirstDraftAlgo();
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
}
