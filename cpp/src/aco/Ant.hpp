#ifndef ACO_ANT_HPP
#define ACO_ANT_HPP
#pragma once

#include "../utils/vector.hpp"
#include "data.hpp"
#include <algorithm>
#include <cmath>
#include <thread>
#include <vector>

namespace aco {
class Ant {
  public:
	/**
	 * 
	 */
	Ant(Parameters params, VertexList possibleVertices, MatrixDouble *costMatrix,
		MatrixDouble *pheromoneMatrix, MatrixDouble *heuristicMatrix)
		: _params(params), _possibleVertices(possibleVertices),
		  _costMatrix(costMatrix), _pheromoneMatrix(pheromoneMatrix),
		  _heuristicMatrix(heuristicMatrix) {
		this->_route = VertexList{this->_params.startVertex};
		utils::vector::removeValue(&(this->_possibleVertices),
								   this->_params.startVertex);
	}

	void Run();
	void Reset(VertexList allVertices);

	bool IsComplete() {
		return this->_runComplete;
	};
	Solution solution() {
		return Solution(this->_cost, this->_route);
	};

  private:
	Parameters _params;
	VertexList _possibleVertices;
	MatrixDouble *_costMatrix;
	MatrixDouble *_pheromoneMatrix;
	MatrixDouble *_heuristicMatrix;
	bool _runComplete = false;
	double _cost = 0.0;
	VertexList _route;

	bool _checkConstraint(double lookahead = 0.0);
	int _pickNextVertex(int currentVertex);
	void _traverse(int fromIndex, int toIndex);
	double _calculateEdgeProbability(int fromIndex, int toIndex);
	double _calculateMoveProbability(int fromIndex, int toIndex, double norm);
	double _calculateProbabilityNorm(int currentVertex);
};
} // namespace aco

#endif
