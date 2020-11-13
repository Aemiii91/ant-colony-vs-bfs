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
		_initMatrices(graph);
	}
	MatrixData() : _size(0){};

	/**
	 * Get the cost on the edge between to vertices.
	 * @param fromIndex The vertex to start from.
	 * @param toIndex The vertex to go to.
	 * @return The edge's cost.
	 */
	double Cost(int fromIndex, int toIndex) {
		return _costMatrix[fromIndex][toIndex];
	};

	/**
	 * Get the probability for the edge between to vertices.
	 * @param fromIndex The vertex to start from.
	 * @param toIndex The vertex to go to.
	 * @return The edge's probability.
	 */
	double Probability(int fromIndex, int toIndex) {
		return _probabilityMatrix[fromIndex][toIndex];
	};

	/**
	 * Deposit pheromone on an edge.
	 * @param fromIndex The vertex to start from.
	 * @param toIndex The vertex to go to.
	 * @param deposit The amount of pheromone to deposit, i.e. the quality of
	 * the ant.
	 */
	void DepositPheromone(int fromIndex, int toIndex, double deposit) {
		_pheromoneMatrix[fromIndex][toIndex] =
			_pheromoneMatrix[fromIndex][toIndex] + deposit;
		_updateProbability(fromIndex, toIndex);
	}

	/**
	 * Run evaporation on the pheromone level on all edges.
	 */
	void EvaporatePheromone() {
		double coefficient = 1 - _evaporation;

		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				_pheromoneMatrix[i][j] *= coefficient;
				_updateProbability(i, j);
			}
		}
	}

  private:
	size_t _size;
	/// Importance of pheromone level.
	double _alpha;
	/// Importance of heuristic information.
	double _beta;
	/// The evaporation rate (evaporation_coefficient = 1 - evaporation_rate).
	double _evaporation;

	/// 2D matrix of the edge's cost.
	std::vector<std::vector<double>> _costMatrix;
	/// 2D matrix of the edge's pheromone level.
	std::vector<std::vector<double>> _pheromoneMatrix;
	/// 2D matrix of the edge's heuristics ((1/cost)^beta).
	std::vector<std::vector<double>> _heuristicMatrix;
	/// 2D matrix of the edge's probabilities (pheromone^alpha * (1/cost)^beta).
	std::vector<std::vector<double>> _probabilityMatrix;

	/**
	 * Initializes the matrices and populates them with values based on the
	 * graph.
	 * @param vectorIDs A pointer to a vector of vertex IDs.
	 * @param graph A pointer to the graph object.
	 */
	void _initMatrices(Graph *graph) {
		auto init = utils::vector::initialize2dVector<double>;
		_costMatrix = init(_size, 0.0);
		_pheromoneMatrix = init(_size, 1.0);
		_heuristicMatrix = init(_size, 0.0);
		_probabilityMatrix = init(_size, 0.0);

		for (int fromIndex = 0; fromIndex < _size; fromIndex++) {
			Node *fromNode = &graph->nodelist[fromIndex];

			for (int toIndex = 0; toIndex < _size; toIndex++) {
				if (fromIndex == toIndex) {
					// skip the matrix diagonals
					continue;
				}

				Node *toNode = &graph->nodelist.at(toIndex);

				double cost = 1.0;
				auto getEdgeCost = [toNode, &cost](Edge *edge) {
					if (edge->dist == toNode->ID) {
						cost = std::max(edge->weight, 1.0);
						return true;
					}
					return false;
				};
				utils::vector::match(&fromNode->edgeList, getEdgeCost);

				double heuristic = std::pow(1.0 / cost, _beta);
				
				_costMatrix[fromIndex][toIndex] = cost;
				_heuristicMatrix[fromIndex][toIndex] = heuristic;
				_probabilityMatrix[fromIndex][toIndex] = heuristic;
			}
		}
	}

	/**
	 * Update the probability for an edge.
	 * @param fromIndex The vertex to start from.
	 * @param toIndex The vertex to go to.
	 */
	void _updateProbability(int fromIndex, int toIndex) {
		double alpha = _alpha;
		double pheromone = _pheromoneMatrix[fromIndex][toIndex];
		double heuristic = _heuristicMatrix[fromIndex][toIndex];
		_probabilityMatrix[fromIndex][toIndex] =
			std::pow(pheromone, alpha) * heuristic;
	}
};
} // namespace aco

#endif
