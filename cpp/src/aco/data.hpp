#ifndef ACO_DATA_HPP
#define ACO_DATA_HPP
#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <indicators/termcolor.hpp>
#include <iostream>
#include <vector>

namespace aco {
typedef std::vector<std::vector<double>> MatrixDouble;
typedef std::vector<int> VertexList;

struct Parameters {
	/// Importance of pheromone level.
	double alpha = 1;
	/// Importance of heuristic information.
	double beta = 20;
	/// The evaporation rate (evaporation_coefficient = 1 - evaporation_rate).
	double evaporation = 0.04;
	/// Constant used to calculate quality of the ants
	double pheromoneConstant = 100.0;
	/// Constraint for the cost of the solution (set 0 for no constraint).
	double costConstraint = 30000;
	/// The ID of the start vertex.
	int startVertex = 0;
	/// Number of ants in the colony.
	int antCount = 50;
	/// Number of iterations to run.
	int iterations = 80;
	/// Number of best ant solutions to use for updating pheromone trails.
	int bestAntLimit = 1;
	/// Whether the ants should return home.
	bool returnHome = true;
	/// Turn multi-threading on or off.
	bool threading = true;
};

struct Solution {
	double cost = 0.0;
	VertexList route = {};

	Solution(){};
	Solution(double cost, VertexList route) : cost(cost), route(route){};

	int score() const {
		size_t size = route.size();
		return route[size - 1] == route[0] ? size - 1 : size;
	};

	friend std::ostream &operator<<(std::ostream &out,
									const Solution &solution) {
		out << "( " << termcolor::reset;
		out << termcolor::bold << termcolor::blue << std::floor(solution.cost)
			<< termcolor::reset;
		out << ", ";
		out << termcolor::bold << termcolor::magenta << solution.score()
			<< termcolor::reset;
		out << " ) ";
		out << termcolor::grey << "= [";

		for (int i = 0; i < solution.route.size(); i++) {
			if (i > 0) {
				out << ", ";
			}
			out << solution.route[i];
		}

		out << "]\n" << termcolor::reset;

		return out;
	};
};
} // namespace aco

#endif
