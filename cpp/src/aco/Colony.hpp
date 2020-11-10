#ifndef ACO_COLONY_HPP
#define ACO_COLONY_HPP
#pragma once

#include <algorithm>
#include <atomic>
#include <cmath>
#include <functional>
#include <indicators/termcolor.hpp>
#include <ThreadPool/ThreadPool.h>
#include <vector>

#include "../graph/graph.h"
#include "../utils/print.hpp"
#include "../utils/vector.hpp"
#include "Ant.hpp"
#include "data.hpp"

namespace aco {
class Colony {
  public:
	double alpha = 1;
	double beta = 20;
	double evaporation = 0.04;
	double pheromoneConstant = 100.0;
	double costConstraint = 30000;
	int startVertix = 0;
	int antCount = 50;
	int iterations = 80;
	int bestAntLimit = 1;
	bool returnHome = true;
	bool threading = true;
	ProgressHandler progressHandler = [](int n, int total) { /* no-op */ };

	Colony(std::vector<int> allVertices, MatrixDouble costMatrix)
		: _allVertices(allVertices), _costMatrix(costMatrix){};
	Colony(Graph *graph);

	Solution Solve(int colonyCount = 80);

  private:
	Solution _solution;
	bool _hasSolution = false;
	int _progressCount = 0;
	int _progressTotal = 100;
	VertixList _allVertices;
	MatrixDouble _costMatrix;
	MatrixDouble _pheromoneMatrix;
	MatrixDouble _heuristicMatrix;

	Solution _solve();
	MatrixDouble _initPheromoneMatrix();
	MatrixDouble _initHeuristicMatrix();
	std::vector<Ant> _initAnts();
	void _runThreads(std::vector<Thread> *threads,
					 std::function<void(int)> job, bool override = true);
	double _calculateSolutionScore(Solution solution);
	std::vector<Solution> _pickBestAntSolutions(std::vector<Ant> *ants);
	int _findWorstSolution(std::vector<Solution> bestSolutions);
	bool _isBetterSolution(Solution newSolution, Solution currentSolution);
	void _updatePheromoneMatrix(Solution bestAntSolution);
	void _evaporatePheromoneMatrix();
	void _progressTick(int stepSize = 1);
	void _setProgressTotal(int value);
};
} // namespace aco

#endif
