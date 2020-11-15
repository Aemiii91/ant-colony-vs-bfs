#ifndef ACO_RUN_HPP
#define ACO_RUN_HPP
#pragma once
// std
#include <chrono>
#include <ctime>
#include <iostream>
// include
#include <indicators/progress_bar.hpp>
#include <termcolor/termcolor.hpp>
// submodules
#include <graph/graph.h>
#include <utils/ArgumentParser.hpp>
// local
#include "Colony.hpp"

namespace aco {
/**
 * Static AntColony class, containing a run function.
 */
class AntColony {
  public:
	/**
	 * Runs the AntColony subprogram.
	 *
	 * @param graph A pointer to the graph.
	 * @param args A pointer to an ArgumentParser object.
	 */
	static void run(Graph *graph, utils::ArgumentParser *args);

  private:
	/**
	 * Print the inputted parameters.
	 *
	 * @param colonyCount The amount of colonies set.
	 * @param params A Parameters object representing the inputted parameters.
	 */
	static void _printParameters(int colonyCount, Parameters params);
	/**
	 * Creates a progress bar object.
	 *
	 * @param maxProgress Total number of ticks.
	 * @return An instance of `indicators::ProgressBar`.
	 */
	static indicators::ProgressBar _createProgressBar(int maxProgress);
	/**
	 * Updates the progress bar.
	 *
	 * @param bar A pointer to the progress bar.
	 * @param n The number of completed ticks.
	 * @param total Total number of ticks.
	 * @param currentStatus String to print after the progress bar.
	 */
	static void _progressBarTick(indicators::ProgressBar *bar, int n, int total,
								 std::string currentStatus);

	// Disallow creating an instance of this object
	AntColony() {}
};
} // namespace aco

#endif
