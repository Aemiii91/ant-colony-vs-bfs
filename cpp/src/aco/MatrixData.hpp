#ifndef ACO_MATRIX_DATA_HPP
#define ACO_MATRIX_DATA_HPP
#pragma once

#include "../graph/graph.h"
#include "Parameters.hpp"
#include <algorithm>
#include <cmath>
#include <functional>

namespace aco {
typedef std::vector<std::vector<double>> MatrixDouble;

class MatrixData {
  public:
	MatrixData() : _size(0) {};
	MatrixData(std::vector<int> vectorIDs, Graph *graph, Parameters *params)
		: _size(graph->nodelist.size()), _params(params) {
		this->_initMatrices(&vectorIDs, graph);
	}

	double Cost(int fromIndex, int toIndex) {
		return this->_cost[fromIndex][toIndex];
	};

	double Pheromone(int fromIndex, int toIndex) {
		return this->_pheromone[fromIndex][toIndex];
	};

	double Probability(int fromIndex, int toIndex) {
		return this->_probability[fromIndex][toIndex];
	};

	void DepositPheromone(int fromIndex, int toIndex, double deposit) {
		this->_pheromone[fromIndex][toIndex] =
			this->_pheromone[fromIndex][toIndex] + deposit;
		this->_updateProbability(fromIndex, toIndex);
	}

	void EvaporatePheromone() {
		double coefficient = 1 - this->_params->evaporation;

		for (int i = 0; i < this->_size; i++) {
			for (int j = 0; j < this->_size; j++) {
				this->_pheromone[i][j] *= coefficient;
				this->_updateProbability(i, j);
			}
		}
	}

  private:
	size_t _size;
	Parameters *_params;

	/// Stores a 2D matrix of the edge's cost.
	MatrixDouble _cost;
	/// Stores a 2D matrix of the edge's pheromone level.
	MatrixDouble _pheromone;
	/// Stores a 2D matrix of the edge's heuristics (1 / cost).
	MatrixDouble _heuristic;
	/// Stores a 2D matrix of the edge's probabilities (pheromone^alpha *
	/// heuristic^beta).
	MatrixDouble _probability;

	void _initMatrices(std::vector<int> *vectorIDs, Graph *graph) {
		this->_cost = utils::vector::initialize2dVector(this->_size, 1.0);
		this->_pheromone = utils::vector::initialize2dVector(this->_size, 1.0);
		this->_heuristic = utils::vector::initialize2dVector(this->_size, 1.0);
		this->_probability =
			utils::vector::initialize2dVector(this->_size, 1.0);

		for (int fromIndex = 0; fromIndex < this->_size; fromIndex++) {
			Node *node = &graph->nodelist[fromIndex];

			for (int toIndex = 0; toIndex < this->_size; toIndex++) {
				if (fromIndex == toIndex) {
					this->_cost[fromIndex][toIndex] = 0.0;
				}
				else {
					int toNode = vectorIDs->at(toIndex);
					double cost = 1.0;
					utils::vector::match(&node->edgeList, [toNode, &cost](Edge *edge) {
						if (edge->dist == toNode) {
							cost = std::max(edge->weight, 1.0);
							return true;
						}
						return false;
					});
					double heuristic =
						std::pow(1.0 / cost, this->_params->beta);
					this->_cost[fromIndex][toIndex] = cost;
					this->_heuristic[fromIndex][toIndex] = heuristic;
					this->_probability[fromIndex][toIndex] = heuristic;
				}
			}
		}
	}

	void _updateProbability(int fromIndex, int toIndex) {
		double alpha = this->_params->alpha;
		double pheromone = this->_pheromone[fromIndex][toIndex];
		double heuristic = this->_heuristic[fromIndex][toIndex];
		this->_probability[fromIndex][toIndex] =
			std::pow(pheromone, alpha) * heuristic;
	}

	template <typename Func>
	void _edit(int fromIndex, int toIndex, Func callback) {
		callback(&this->_cost[fromIndex][toIndex],
				 &this->_pheromone[fromIndex][toIndex],
				 &this->_heuristic[fromIndex][toIndex],
				 &this->_probability[fromIndex][toIndex]);
	}
};
} // namespace aco

#endif
