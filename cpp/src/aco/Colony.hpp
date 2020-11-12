#ifndef ACO_COLONY_HPP
#define ACO_COLONY_HPP
#pragma once

#include <ThreadPool/ThreadPool.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <functional>
#include <indicators/termcolor.hpp>
#include <vector>

#include "../graph/graph.h"
#include "../utils/print.hpp"
#include "../utils/vector.hpp"
#include "Ant.hpp"
#include "Parameters.hpp"
#include "Solution.hpp"
#include "MatrixData.hpp"

namespace aco {
class Colony {
  public:
	/// Set this to subscribe to progress updates.
	std::function<void(int, int)> progressHandler = [](int, int) {};
	std::function<void(double, int, int, int)> solutionHandler =
		[](double cost, int score, int iteration, int colonyID) {};

	/**
	 * Colony constructor to initialize with a Graph object.
	 *
	 * @param graph A pointer to the Graph object.
	 */
	Colony(Graph *graph, Parameters params);

	/**
	 * Launch the algorithm.
	 *
	 * Alternatively set colonyCount to the number of colonies to solve, and get
	 * the best overall solution.
	 *
	 * @param colonyCount Number of colonies to solve.
	 * @return The best solution.
	 */
	Solution Solve(int colonyCount = 1);

  private:
	/// Stores the received parameters.
	Parameters _params;
	/// Stores the current best solution.
	Solution _solution;
	/// Whether a solution has been found.
	bool _hasSolution = false;
	/// Cumulative value of cycles done (sent to progressHandler).
	int _progressCount = 0;
	/// Total number of cycles to run (sent to progressHandler).
	int _progressTotal = 100;
	/// Stores a vector of vertex IDs.
	std::vector<int> _vertexIDs;
	/// Stores a vector of vertex indexes.
	std::vector<int> _allVertices;
	/// Stores a collection of 2D matrices.
	MatrixData _matrixData;

	/// Solves this colony.
	Solution _solve();
	/// Initializes the pheromone, heuristic and probability matrices.
	void _initMatrices();
	/// Initializes the ants.
	void _initAnts(std::vector<Ant> *ants);
	void _runAnts(ThreadPool *pool, std::vector<Ant> *ants);
	void _resetAnts(std::vector<Ant> *ants);
	/// Returns true if all ants are done.
	bool _checkAntsComplete(std::vector<Ant> *ants);
	std::vector<Solution> _pickBestAntSolutions(std::vector<Ant> *ants);
	bool _assessSolution(Solution solution);
	double _calculateSolutionScore(Solution solution);
	void _depositPheromone(Solution antSolution);
	void _progressTick(int stepSize = 1);
	void _setProgressTotal(int value);
	/// Converts internal solution (with indexes) to external solution (with
	/// IDs).
	Solution _exportSolution(Solution internalSolution);
};
} // namespace aco

#endif
