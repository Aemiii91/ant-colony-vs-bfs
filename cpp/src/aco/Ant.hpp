#ifndef ACO_ANT_HPP
#define ACO_ANT_HPP
#pragma once
// std
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iterator>
#include <random>
#include <thread>
// submodules
#include <utils/vector.hpp>
// local
#include "MatrixData.hpp"
#include "Parameters.hpp"
#include "Solution.hpp"

namespace aco {
class Ant {
  public:
	/**
	 * Constructs an ant.
	 *
	 * @param allVertices A list of all the vertices' indexes.
	 * @param params A pointer to the Colony's parameters
	 * @param matrixData A pointer to the Colony's matrix data.
	 */
	Ant(std::vector<int> allVertices, Parameters *params,
		MatrixData *matrixData)
		: _params(params), _matrixData(matrixData),
		  _random(std::random_device{}()) {
		this->Init(allVertices);
	}

	/**
	 * Starts the ant. Ant will construct a route and stop at either
	 * `costConstraint` or when it runs out of possible vertices.
	 */
	void Run();
	/**
	 * Reset the ant.
	 *
	 * @param allVertices A list of all the vertices' indexes.
	 */
	void Init(std::vector<int> allVertices) {
		_runComplete = false;
		_cost = 0.0;
		_route = std::vector<int>{_params->startVertex};
		_possibleVertices = allVertices;
		utils::vector::removeValue(&(_possibleVertices), _params->startVertex);
	}

	/**
	 * Check if the ant is done.
	 *
	 * @return True if ant is done.
	 */
	bool IsComplete() {
		return _runComplete;
	};
	/**
	 * Extract the ant's solution.
	 *
	 * @return A `Solution` object, with the ant's route, cost and score.
	 */
	Solution solution() {
		return Solution(_cost, _route);
	};

  private:
	/// Stores a pointer to the Colony's parameters.
	Parameters *_params;
	/// Stores a pointer to the Colony's matrix data.
	MatrixData *_matrixData;
	/// A list of possible vertices.
	std::vector<int> _possibleVertices;
	/// A Mersenne Twister pseudo-random generator of 32-bit numbers.
	std::mt19937 _random;
	/// True if the ant is done.
	bool _runComplete;
	/// Cumulative cost variable.
	double _cost;
	/// Container for the constructed route.
	std::vector<int> _route;

	/**
	 * If `costConstraint` is set, check whether the constraint is met.
	 *
	 * @param currentVertex Vertex the ant moves from.
	 * @param nextVertex Vertex the ant moves to.
	 * @return True if the move can be made.
	 */
	bool _checkMove(int currentVertex, int nextVertex);
	/**
	 * Calculates the normalized probabilities for each possible vertex, and
	 * picks one of them.
	 *
	 * @param currentVertex The vertex the ant is currently on.
	 * @return The picked vertix (index).
	 */
	int _pickNextVertex(int currentVertex);
	/**
	 * Calculates normalized probabilities (attractiveness).
	 *
	 * @param currentVertex The vertex the ant is currently on.
	 * @param norm The normalization value.
	 * @return A vector of normalized probabilities.
	 */
	std::vector<double> _attractivenessVector(int currentVertex, double norm);
	/**
	 * Performs a weighted choice on a vector of attractiveness.
	 *
	 * @param attractiveness A vector of the vertices' attractiveness.
	 * @return The index of the weighted choice.
	 */
	int _weightedChoice(std::vector<double> *attractiveness);
	/**
	 * Moves the ant.
	 *
	 * Adds the next vertex to the route, and removes it from
	 * `possibleVertices`. Adds the cost of the move to the cumulative cost
	 * variable.
	 *
	 * @param currentVertex Vertex the ant moves from.
	 * @param nextVertex Vertex the ant moves to.
	 */
	void _traverse(int currentVertex, int nextVertex);
	/**
	 * Gathers the `norm` value, which is the sum of all the possible edges
	 * probabilities.
	 *
	 * @param currentVertex The vertex the ant is currently on.
	 * @return A `norm` value.
	 */
	double _probabilityNorm(int currentVertex);
};
} // namespace aco

#endif
