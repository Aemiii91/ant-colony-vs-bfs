#ifndef ACO_ANT_HPP
#define ACO_ANT_HPP
#pragma once
// std
#include <algorithm>
#include <cmath>
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
		: _params(params), _matrixData(matrixData) {
		int startVertex = this->_params->startVertex;
		this->_route = std::vector<int>{startVertex};
		this->_possibleVertices = allVertices;
		utils::vector::removeValue(&(this->_possibleVertices), startVertex);
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
	void Reset(std::vector<int> allVertices);

	/**
	 * Check if the ant is done.
	 *
	 * @return True if ant is done.
	 */
	bool IsComplete() {
		return this->_runComplete;
	};
	/**
	 * Extract the ant's solution.
	 *
	 * @return A `Solution` object, with the ant's route, cost and score.
	 */
	Solution solution() {
		return Solution(this->_cost, this->_route);
	};

  private:
	/// Stores a pointer to the Colony's parameters.
	Parameters *_params;
	/// Stores a pointer to the Colony's matrix data.
	MatrixData *_matrixData;
	/// A list of possible vertices.
	std::vector<int> _possibleVertices;
	/// True if the ant is done.
	bool _runComplete = false;
	/// Cumulative cost variable.
	double _cost = 0.0;
	/// Container for the constructed route.
	std::vector<int> _route;

	/**
	 * If `costConstraint` is set, check whether the constraint is met.
	 *
	 * @param lookahead A lookahead value added to the current cost when
	 * comparing.
	 * @return True if the `cost+lookahead` value is lower than the
	 * `costConstraint`.
	 */
	bool _checkConstraint(double lookahead = 0.0);
	/**
	 * Calculates the normalized probabilities for each possible vertex, and
	 * picks one of them.
	 *
	 * @param currentVertex The vertex the ant is currently on.
	 * @return The picked vertix (index).
	 */
	int _pickNextVertex(int currentVertex);
	/**
	 * Moves the ant. Adds the next vertex to the route, and removes it from
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
