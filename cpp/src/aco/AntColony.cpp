#include "AntColony.hpp"

using namespace aco;

void AntColony::run(Graph *graph, utils::ArgumentParser *args) {
	int colonyCount = 1;
	Parameters params;
	args->Get("--colonies", &colonyCount);
	args->Get("--alpha", &params.alpha);
	args->Get("--beta", &params.beta);
	args->Get("--evaporation", &params.evaporation);
	args->Get("--pheromone", &params.pheromoneConstant);
	args->Get("--cost", &params.costConstraint);
	args->Get("--start", &params.startVertex);
	args->Get("--ants", &params.antCount);
	args->Get("--iterations", &params.iterations);
	args->Get("--best_ants", &params.bestAntLimit);
	args->Get("--time", &params.timeAvailable);
	bool smacMode = args->Exists("--smac_mode");
	params.returnHome = !args->Exists("--noreturn");
	params.threading = !args->Exists("--nothreading");
	bool showProgress = args->Exists("--progress");
	bool showProgress2 = args->Exists(("--progress2"));

	//if (!smacMode && !showProgress2)
	//	_printParameters(colonyCount, params);

	// spawn the colony
	Colony colony(graph, params);

	// initialize progress bar
	int totalCycles = colonyCount * params.antCount * params.iterations;
	indicators::ProgressBar bar = _createProgressBar(totalCycles);
	std::string currentStatus = "";
	int currentIterations = 0;

	if (showProgress) {
		// print progress bar legend
		std::cout
			<< termcolor::grey << std::left << std::setw(28) << "Progress"
			<< "[Elapsed<remaining] cycles  ( solution ) @ iteration (colony)"
			<< termcolor::reset << std::endl;

		// set solution handler (it's called whenever a better solution is
		// found)
		colony.solutionHandler = [&currentStatus,
								  &params](double cost, int score,
										   int iteration, int colonyID) {
			// set status to current best solution
			std::stringstream s;
			s << "( " << std::floor(cost) << ", " << score << " ) @ "
			  << (iteration + 1) << "/" << params.iterations;
			if (colonyID >= 0) {
				s << " (" << (colonyID + 1) << ")";
			}
			currentStatus = s.str();
		};

		// set progress handler (to update the progress bar)
		colony.progressHandler = [&bar, &currentStatus](int n, int total) {
			_progressBarTick(&bar, n, total, currentStatus);
		};
	}
	if (showProgress2) {
        colony.solutionHandler = [&currentStatus,
            &params](double cost, int score,
                     int iteration, int colonyID) {
			std::cout << std::floor(cost) << ", " << score << std::endl;
		};
	}

	// start timer
	auto start = std::chrono::high_resolution_clock::now();

	// solve the ant colony
	Solution bestSolution = colony.Solve(colonyCount);

	// stop timer
	auto stop = std::chrono::high_resolution_clock::now();

	if (showProgress) {
		// update the progress bar to 100%
		//_progressBarTick(&bar, totalCycles, totalCycles, currentStatus);
	}

	if (smacMode) {
		std::cout << bestSolution.score;
	}

	if (showProgress2) {
		std::cout << std::floor(bestSolution.cost) << ", " << bestSolution.score << std::endl;
	}
	// calculate and print runtime
	else {
		auto duration =
			std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		char s[20];
		snprintf(s, 20, "%.3fs\n", (double)duration.count() / 1000000);
		std::cout << termcolor::yellow << s << termcolor::reset;

		// print the solution
		std::cout << bestSolution;
	}
}

void AntColony::_printParameters(int colonyCount, Parameters params) {
	if (colonyCount > 1) {
		std::cout << colonyCount << " colonies, ";
	}
	std::cout << params.antCount << " ants, ";
	std::cout << params.iterations << " iterations";

	std::cout << termcolor::grey;
	std::cout << " [ alpha=" << params.alpha << ", beta=" << params.beta
			  << ", evaporation=" << params.evaporation
			  << ", pheromone=" << params.pheromoneConstant;
	if (params.bestAntLimit != 1) {
		std::cout << ", best_ants=" << params.bestAntLimit;
	}
	if (params.startVertex != 0) {
		std::cout << ", start=" << params.startVertex;
	}
	if (params.costConstraint != 0) {
		std::cout << ", cost=" << params.costConstraint;
	}
	std::cout << ", time limit=" << params.timeAvailable << " sec";

	std::cout << " ]" << termcolor::reset << std::endl;
}

indicators::ProgressBar AntColony::_createProgressBar(int maxProgress) {
	namespace opt = indicators::option;
	std::string indicator = "#";

	return indicators::ProgressBar{
		opt::BarWidth{20},
		opt::ShowElapsedTime{true},
		opt::ShowRemainingTime{true},
		opt::MaxProgress{maxProgress},
		opt::Fill{indicator},
		opt::Lead{indicator},
		opt::ForegroundColor{indicators::Color::green},
		opt::FontStyles{
			std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};
}

void AntColony::_progressBarTick(indicators::ProgressBar *bar, int n, int total,
								 std::string currentStatus) {
	std::stringstream prefix, postfix;
	prefix << std::setw(3) << (int)std::ceil((double)n / total * 100) << "% ";
	postfix << std::min(n, total) << "/" << total << "  " << currentStatus;

	if (!bar->is_completed()) {
		bar->set_option(indicators::option::PrefixText{prefix.str()});
		bar->set_option(indicators::option::PostfixText{postfix.str()});
		bar->tick();
	}
}
