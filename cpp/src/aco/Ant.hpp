#ifndef ACO_ANT_HPP
#define ACO_ANT_HPP
#pragma once

#include "../utils/vector.hpp"
#include "MatrixData.hpp"
#include "Parameters.hpp"
#include "Solution.hpp"
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
	Ant(std::vector<int> allVertices, Parameters *params, MatrixData *matrixData)
		: _params(params), _matrixData(matrixData) {
		this->_route = std::vector<int>{this->_params->startVertex};
		this->_possibleVertices = allVertices;
		utils::vector::removeValue(&(this->_possibleVertices),
								   this->_params->startVertex);
	}

	void Run();
	void Reset(std::vector<int> allVertices);

	bool IsComplete() {
		return this->_runComplete;
	};
	Solution solution() {
		return Solution(this->_cost, this->_route);
	};

  private:
	Parameters *_params;
	MatrixData *_matrixData;
	std::vector<int> _possibleVertices;
	bool _runComplete = false;
	double _cost = 0.0;
	std::vector<int> _route;

	bool _checkConstraint(double lookahead = 0.0);
	int _pickNextVertex(int currentVertex);
	void _traverse(int fromIndex, int toIndex);
	double _probabilityNorm(int currentVertex);
};
} // namespace aco

#endif
