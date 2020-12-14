#include "AntColony.hpp"

using namespace aco;

void AntColony::AddArguments(argparse::ArgumentParser *args) {
	args->add_argument("--colonies").default_value(1);
	args->add_argument("--alpha").default_value(_params.alpha);
	args->add_argument("--beta").default_value(_params.beta);
	args->add_argument("--evaporation").default_value(_params.evaporation);
	args->add_argument("--pheromone").default_value(_params.pheromoneConstant);
	// args->add_argument("--cost").default_value(_params.costConstraint);
	// args->add_argument("--start").default_value(_params.startVertex);
	args->add_argument("--ants").default_value(_params.antCount);
	// args->add_argument("--iterations").default_value(_params.iterations);
	args->add_argument("--best_ants").default_value(_params.bestAntLimit);
	args->add_argument("--noreturn").default_value(false).implicit_value(true);
	args->add_argument("--nothreading")
		.default_value(false)
		.implicit_value(true);
	args->add_argument("--progress").default_value(false).implicit_value(true);
}

void AntColony::Run(argparse::ArgumentParser *args) {
	_params.costConstraint = this->costConstraint;
	_params.startVertex = this->startVertex;
	_params.iterations = this->iterationLimit;
	_params.alpha = args->get<double>("--alpha");
	_params.beta = args->get<double>("--beta");
	_params.evaporation = args->get<double>("--evaporation");
	_params.pheromoneConstant = args->get<double>("--pheromone");
	_params.antCount = args->get<int>("--ants");
	_params.bestAntLimit = args->get<int>("--best_ants");
	_params.returnHome = !args->get<bool>("--noreturn");
	_params.threading = !args->get<bool>("--nothreading");
	int colonyCount = args->get<int>("--colonies");
	bool showProgress = args->get<bool>("--progress");

	// print all parameters
	_printParameters(colonyCount);

	// spawn the colony
	Colony colony(&this->graph, _params);

	// initialize progress bar
	int totalCycles = colonyCount * _params.antCount * _params.iterations;
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
		colony.solutionHandler = [&currentStatus, this](double cost, int score,
														int iteration,
														int colonyID) {
			// set status to current best solution
			std::stringstream s;
			s << "( " << std::floor(cost) << ", " << score << " ) @ "
			  << (iteration + 1) << "/" << this->_params.iterations;
			if (colonyID >= 0) {
				s << " (" << (colonyID + 1) << ")";
			}
			currentStatus = s.str();
		};

		// set progress handler (to update the progress bar)
		colony.progressHandler = [&bar, &currentStatus, this](int n,
															  int total) {
			_progressBarTick(&bar, n, total, currentStatus);
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
		_progressBarTick(&bar, totalCycles, totalCycles, currentStatus);
	}

	// calculate and print runtime
	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	char s[20];
	snprintf(s, 20, "%.3fs\n", (double)duration.count() / 1000000);
	std::cout << termcolor::yellow << s << termcolor::reset;

	// print the solution
	std::cout << bestSolution;
}

void AntColony::_printParameters(int colonyCount) {
	if (colonyCount > 1) {
		std::cout << colonyCount << " colonies, ";
	}
	std::cout << _params.antCount << " ants, ";
	std::cout << _params.iterations << " iterations";

	std::cout << termcolor::grey;
	std::cout << " [ alpha=" << _params.alpha << ", beta=" << _params.beta
			  << ", evaporation=" << _params.evaporation
			  << ", pheromone=" << _params.pheromoneConstant;
	if (_params.bestAntLimit != 1) {
		std::cout << ", best_ants=" << _params.bestAntLimit;
	}
	if (_params.startVertex != 0) {
		std::cout << ", start=" << _params.startVertex;
	}
	if (_params.costConstraint != 0) {
		std::cout << ", cost=" << _params.costConstraint;
	}
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
