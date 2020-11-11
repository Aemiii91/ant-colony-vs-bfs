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
	/// Set this to subscribe to progress updates.
	std::function<void(int,int)> progressHandler = [](int, int) { /* no-op */ };
	std::function<void(Solution,int,int)> solutionHandler = [](Solution, int, int) { /* no-op */ };

	/**
	 * Colony constructor to initialize with a Graph object.
	 * 
	 * @param graph A pointer to the Graph object.
	 */
	Colony(Graph *graph, Parameters params);

	/**
	 * Launch the algorithm.
	 * 
	 * Alternatively set colonyCount to the number of colonies to solve, and get the best overall solution.
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
	VertexList _vertexIDs;
	/// Stores a vector of vertex indexes.
	VertexList _allVertices;
	/// Stores a 2D matrix of the edge's cost.
	MatrixDouble _costMatrix;
	/// Stores a 2D matrix of the edge's pheromone level.
	MatrixDouble _pheromoneMatrix;
	/// Stores a 2D matrix of the edge's heuristic (1 / cost).
	MatrixDouble _heuristicMatrix;

	/// Solves this colony.
	Solution _solve();
	/// Creates a 2D matrix with default value 1.0.
	void _initPheromoneMatrix();
	/// Creates a 2D matrix with the edge's heuristic values.
	void _initHeuristicMatrix();
	/// Initializes the ants.
	void _initAnts(std::vector<Ant> *ants);
	std::vector<Solution> _pickBestAntSolutions(std::vector<Ant> *ants);
	int _findWorstSolution(std::vector<Solution> bestSolutions);
	bool _assessSolution(Solution solution);
	bool _isBetterSolution(Solution newSolution, Solution currentSolution);
	double _calculateSolutionScore(Solution solution);
	void _updatePheromoneMatrix(Solution bestAntSolution);
	void _evaporatePheromoneMatrix();
	void _progressTick(int stepSize = 1);
	void _setProgressTotal(int value);
	/// Converts internal solution (with indexes) to external solution (with IDs).
	Solution _exportSolution(Solution internalSolution);
};
} // namespace aco

#endif
