#ifndef ACO_COLONY_HPP
#define ACO_COLONY_HPP
#pragma once
// std
#include <algorithm>
#include <atomic>
#include <cmath>
#include <functional>
// include
#include <ThreadPool/ThreadPool.h>
#include <termcolor/termcolor.hpp>
// submodules
#include <graph/graph.h>
#include <utils/printc.hpp>
#include <utils/vector.hpp>
// local
#include "Ant.hpp"
#include "MatrixData.hpp"
#include "Parameters.hpp"
#include "Solution.hpp"

namespace aco {
/**
 * An ant colony class.
 */
class Colony {
  public:
	/// Set this to subscribe to progress updates.
	std::function<void(int, int)> progressHandler = [](int, int) {};
	/// Set this to subscribe to solution updates.
	std::function<void(double, int, int, int)> solutionHandler =
		[](double cost, int score, int iteration, int colonyID) {};

	/**
	 * Colony constructor to initialize with a Graph object.
	 *
	 * @param graph A pointer to the Graph object.
	 * @param params A `Parameters` object.
	 */
	Colony(Graph *graph, Parameters params)
		: _graphNodes(&graph->nodelist), _params(params) {
		size_t size = _graphNodes->size();

		// create the list of indexes
		for (int index = 0; index < size; index++) {
			_allVertices.push_back(index);
		}

		// initialize the matrices
		_matrixData = MatrixData(graph, &_params);
	}

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
	Solution _bestInColony;
	/// Whether a solution has been found.
	bool _hasSolution = false;
	/// Stores a vector of vertex indexes.
	std::vector<int> _allVertices;
	/// Stores a collection of 2D matrices.
	MatrixData _matrixData;
	/// Stores a pointer to the graph (used in `_exportSolution`).
	std::vector<Node> *_graphNodes;
	/// Cumulative value of cycles done (sent to progressHandler).
	int _progressCount = 0;
	/// Total number of cycles to run (sent to progressHandler).
	int _progressTotal = 100;
	/// A shared thread pool for multi-threading
	static ThreadPool _threadPool;

	/**
	 * Solves this colony.
	 */
	void _solve();
	/**
	 * Initializes the ants.
	 *
	 * @param ants A pointer to the lists of ants.
	 */
	void _initAnts(std::vector<Ant> *ants);
	/**
	 * Runs the ants (with multi-threading).
	 *
	 * @param pool A pointer to a ThreadPool object.
	 * @param ants A pointer to the lists of ants.
	 */
	void _runAnts(std::vector<Ant> *ants);
	/**
	 * Resets the ants.
	 *
	 * @param ants A pointer to the lists of ants.
	 */
	void _resetAnts(std::vector<Ant> *ants);
	/**
	 * Checks whether any ant is incomplete.
	 *
	 * @param ants A pointer to the lists of ants.
	 * @return True if all ants are done.
	 */
	bool _checkAntsComplete(std::vector<Ant> *ants);
	/**
	 * Gets the best ants' solutions. The number of best solutions is determined
	 * by the `bestAntLimit` Colony-parameter.
	 *
	 * @param ants A pointer to the lists of ants.
	 * @return A list of the best ants' solutions.
	 */
	std::vector<Solution> _pickBestAnts(std::vector<Ant> *ants);
	/**
	 * Compares the solution to the current best. If better, then sets it as
	 * current best.
	 *
	 * @param solution The new solution to compare.
	 * @return True if the solution was the new best.
	 */
	bool _assessSolution(Solution solution, int iteration, int colonyID = -1);
	/**
	 * Deposit pheromone based on an ant's solution.
	 *
	 * @param antSolution The ant's solution.
	 */
	void _depositPheromone(Solution antSolution);
	/**
	 * Converts the solution's indexes to IDs.
	 *
	 * @param solution A solution with a route-list of indexes.
	 * @return A solution with a route-list of IDs.
	 */
	Solution _exportSolution(Solution solution);
	/**
	 * Adds 1 to the `progressCount`, and calls the `progressHandler`.
	 */
	void _progressTick();
};
} // namespace aco

#endif
