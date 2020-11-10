#ifndef ACO_ANT_HPP
#define ACO_ANT_HPP
#pragma once

#include "data.hpp"
#include <algorithm>
#include <cmath>
#include <thread>
#include <vector>

namespace aco {
class Ant {
  public:
	VertixList possibleVertices;
	MatrixDouble *costMatrix;
	MatrixDouble *pheromoneMatrix;
	MatrixDouble *heuristicMatrix;
	double alpha;
	double beta;
	double costConstraint;
	int startVertix;
	bool runComplete = false;
	bool returnHome;
	/**
	 * @param alpha importance of pheromone level
	 * @param beta importance of heuristic information
	 */
	Ant(int startVertix, VertixList possibleVertices, MatrixDouble *costMatrix,
		MatrixDouble *pheromoneMatrix, MatrixDouble *heuristicMatrix,
		double alpha, double beta, double costConstraint, bool returnHome)
		: startVertix(startVertix), possibleVertices(possibleVertices),
		  costMatrix(costMatrix), pheromoneMatrix(pheromoneMatrix),
		  heuristicMatrix(heuristicMatrix), alpha(alpha), beta(beta),
		  costConstraint(costConstraint), returnHome(returnHome) {
		this->_route = VertixList{this->startVertix};
		this->_removeFromVertixList(&(this->possibleVertices),
									this->startVertix);
	}

	void Run();
	void Reset(VertixList allVertices);

	Solution solution() {
		return Solution(this->_cost, this->_route);
	};

  private:
	double _cost = 0.0;
	VertixList _route;
	bool _checkConstraint(double lookahead = 0.0);
	int _pickNextVertix(int currentVertix);
	void _traverse(int fromIndex, int toIndex);
	void _removeFromVertixList(VertixList *vert, int value);
	double _calculateEdgeProbability(int fromIndex, int toIndex);
	double _calculateMoveProbability(int fromIndex, int toIndex, double norm);
	double _calculateProbabilityNorm(int currentVertix);
};
} // namespace aco

#endif
