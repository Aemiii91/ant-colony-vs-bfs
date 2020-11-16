#ifndef ACO_PARAMETERS_HPP
#define ACO_PARAMETERS_HPP
#pragma once

namespace aco {
/**
 * A struct to contain the colony's parameters.
 */
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
	/// The index value of the start vertex.
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
} // namespace aco

#endif
