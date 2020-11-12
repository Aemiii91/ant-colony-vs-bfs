#ifndef ACO_MATRIX_DATA_HPP
#define ACO_MATRIX_DATA_HPP
#pragma once
// std
#include <algorithm>
#include <cmath>
#include <functional>
// submodules
#include <graph/graph.h>
#include <utils/vector.hpp>
// local
#include "Parameters.hpp"

namespace aco {
/**
 * Stores 2D matrices of the graph's cost, pheromone level, heuristic data, and
 * probabilities.
 */
class MatrixData {
  public:
	/**
	 * Constructs a collection of 2D matrices based on the graph's data.
	 * @param graph A pointer to the graph object.
	 * @param params A pointer to the colony's `Parameters` object.
	 */
	MatrixData(Graph *graph, Parameters *params)
		: _size(graph->nodelist.size()), _alpha(params->alpha),
		  _beta(params->beta), _evaporation(params->evaporation) {
		this->_initMatrices(graph);
	}
	MatrixData() : _size(0){};

	/**
	 * Get the cost on the edge between to vertices.
	 * @param fromIndex The vertex to start from.
	 * @param toIndex The vertex to go to.
	 * @return The edge's cost.
	 */
	double Cost(int fromIndex, int toIndex) {
		return this->_cost[fromIndex][toIndex];
	};

	/**
	 * Get the probability for the edge between to vertices.
	 * @param fromIndex The vertex to start from.
	 * @param toIndex The vertex to go to.
	 * @return The edge's probability.
	 */
	double Probability(int fromIndex, int toIndex) {
		return this->_probability[fromIndex][toIndex];
	};

	/**
	 * Deposit pheromone on an edge.
	 * @param fromIndex The vertex to start from.
	 * @param toIndex The vertex to go to.
	 * @param deposit The amount of pheromone to deposit, i.e. the quality of
	 * the ant.
	 */
	void DepositPheromone(int fromIndex, int toIndex, double deposit) {
		this->_pheromone[fromIndex][toIndex] =
			this->_pheromone[fromIndex][toIndex] + deposit;
		this->_updateProbability(fromIndex, toIndex);
	}

	/**
	 * Run evaporation on the pheromone level on all edges.
	 */
	void EvaporatePheromone() {
		double coefficient = 1 - this->_evaporation;

		for (int i = 0; i < this->_size; i++) {
			for (int j = 0; j < this->_size; j++) {
				this->_pheromone[i][j] *= coefficient;
				this->_updateProbability(i, j);
			}
		}
	}

  private:
	size_t _size;
	double _alpha;
	double _beta;
	double _evaporation;

	/// 2D matrix of the edge's cost.
	std::vector<std::vector<double>> _cost;
	/// 2D matrix of the edge's pheromone level.
	std::vector<std::vector<double>> _pheromone;
	/// 2D matrix of the edge's heuristics ((1/cost)^beta).
	std::vector<std::vector<double>> _heuristic;
	/// 2D matrix of the edge's probabilities (pheromone^alpha * (1/cost)^beta).
	std::vector<std::vector<double>> _probability;

	/**
	 * Initializes the matrices and populates them with values based on the
	 * graph.
	 * @param vectorIDs A pointer to a vector of vertex IDs.
	 * @param graph A pointer to the graph object.
	 */
	void _initMatrices(Graph *graph) {
		auto init = utils::vector::initialize2dVector<double>;
		this->_cost = init(this->_size, 0.0);
		this->_pheromone = init(this->_size, 1.0);
		this->_heuristic = init(this->_size, 0.0);
		this->_probability = init(this->_size, 0.0);

		for (int fromIndex = 0; fromIndex < this->_size; fromIndex++) {
			Node *fromNode = &graph->nodelist[fromIndex];

			for (int toIndex = 0; toIndex < this->_size; toIndex++) {
				if (fromIndex == toIndex) {
					// skip the matrix diagonals
					continue;
				}

				Node *toNode = &graph->nodelist.at(toIndex);
				double cost = 1.0;
				utils::vector::match(
					&fromNode->edgeList, [toNode, &cost](Edge *edge) {
						if (edge->dist == toNode->ID) {
							cost = std::max(edge->weight, 1.0);
							return true;
						}
						return false;
					});
				double heuristic = std::pow(1.0 / cost, this->_beta);
				this->_cost[fromIndex][toIndex] = cost;
				this->_heuristic[fromIndex][toIndex] = heuristic;
				this->_probability[fromIndex][toIndex] = heuristic;
			}
		}
	}

	/**
	 * Update the probability for an edge.
	 * @param fromIndex The vertex to start from.
	 * @param toIndex The vertex to go to.
	 */
	void _updateProbability(int fromIndex, int toIndex) {
		double alpha = this->_alpha;
		double pheromone = this->_pheromone[fromIndex][toIndex];
		double heuristic = this->_heuristic[fromIndex][toIndex];
		this->_probability[fromIndex][toIndex] =
			std::pow(pheromone, alpha) * heuristic;
	}
};
} // namespace aco

#endif
