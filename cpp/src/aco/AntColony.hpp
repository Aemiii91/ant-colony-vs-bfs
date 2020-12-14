#ifndef ACO_RUN_HPP
#define ACO_RUN_HPP
#pragma once
// std
#include <chrono>
#include <ctime>
#include <iostream>
// include
#include <argparse/argparse.hpp>
#include <indicators/progress_bar.hpp>
#include <termcolor/termcolor.hpp>
// submodules
#include <common/BaseAlgorithmRunner.hpp>
#include <graph/graph.h>
#include <utils/ArgumentParser.hpp>
// local
#include "Colony.hpp"

namespace aco {
/**
 * Static AntColony class, containing a run function.
 */
class AntColony : public common::BaseAlgorithmRunner {
  public:
	void AddArguments(argparse::ArgumentParser *args) override;
	void Run(argparse::ArgumentParser *args) override;

  private:
	Parameters _params;
	void _parseArguments(argparse::ArgumentParser *args);
	/**
	 * Print the inputted parameters.
	 *
	 * @param colonyCount The amount of colonies set.
	 */
	void _printParameters(int colonyCount);
	/**
	 * Creates a progress bar object.
	 *
	 * @param maxProgress Total number of ticks.
	 * @return An instance of `indicators::ProgressBar`.
	 */
	indicators::ProgressBar _createProgressBar(int maxProgress);
	/**
	 * Updates the progress bar.
	 *
	 * @param bar A pointer to the progress bar.
	 * @param n The number of completed ticks.
	 * @param total Total number of ticks.
	 * @param currentStatus String to print after the progress bar.
	 */
	void _progressBarTick(indicators::ProgressBar *bar, int n, int total,
						  std::string currentStatus);
};
} // namespace aco

#endif
