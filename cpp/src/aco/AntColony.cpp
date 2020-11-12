#include "AntColony.hpp"

using namespace aco;

void AntColony::run(Graph *graph, utils::ArgumentParser *args) {
	time_t t;
	srand(time(&t));

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
	params.returnHome = !args->Exists("--noreturn");
	params.threading = !args->Exists("--nothreading");
	bool showProgress = args->Exists("--progress");

	_printParameters(colonyCount, params);

	Colony colony(graph, params);

	int totalCycles = colonyCount * params.antCount * params.iterations;
	indicators::ProgressBar bar = _createProgressBar(totalCycles);

	std::string currentStatus = "";
	int currentIterations = 0;

	colony.solutionHandler = [&currentStatus, &params](double cost, int score,
													   int iteration,
													   int colonyID) {
		std::stringstream s;
		s << "( " << std::floor(cost) << ", " << score << " ) @ "
		  << (iteration + 1) << "/" << params.iterations;
		if (colonyID >= 0) {
			s << " (" << (colonyID + 1) << ")";
		}
		currentStatus = s.str();
	};

	if (showProgress) {
		std::cout
			<< termcolor::grey << std::left << std::setw(28) << "Progress"
			<< "[Elapsed<remaining] cycles  ( solution ) @ iteration (colony)"
			<< termcolor::reset << std::endl;

		colony.progressHandler = [&bar, &currentStatus](int n, int total) {
			_progressBarTick(&bar, n, total, currentStatus);
		};
	}

	auto start = std::chrono::high_resolution_clock::now();
	Solution bestSolution = colony.Solve(colonyCount);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	if (showProgress) {
		_progressBarTick(&bar, totalCycles - 1, totalCycles, currentStatus);
	}

	char s[20];
	snprintf(s, 20, "%.3fs\n", (double)duration.count() / 1000000);
	printc::yellow(s);

	std::cout << bestSolution;
}

void AntColony::_printParameters(int colonyCount, Parameters params) {
	std::stringstream paramStr;

	if (colonyCount > 1) {
		paramStr << colonyCount << " colonies, ";
	}
	paramStr << params.antCount << " ants, ";
	paramStr << params.iterations << " iterations";

	printc::bold(paramStr.str());

	std::stringstream extraStr;
	extraStr << " [ alpha=" << params.alpha << ", beta=" << params.beta
			 << ", evaporation=" << params.evaporation
			 << ", pheromone=" << params.pheromoneConstant;
	if (params.bestAntLimit != 1) {
		extraStr << ", best_ants=" << params.bestAntLimit;
	}
	if (params.startVertex != 0) {
		extraStr << ", start=" << params.startVertex;
	}
	if (params.costConstraint != 0) {
		extraStr << ", cost=" << params.costConstraint;
	}
	extraStr << " ]\n";

	printc::boldGrey(extraStr.str());
}

indicators::ProgressBar AntColony::_createProgressBar(int maxProgress) {
	namespace opt = indicators::option;
	std::string indicator = "#";
	auto fgColor = printc::colorsEnabled() ? indicators::Color::green
										   : indicators::Color::white;

	return indicators::ProgressBar{
		opt::BarWidth{20},
		opt::ShowElapsedTime{true},
		opt::ShowRemainingTime{true},
		opt::MaxProgress{maxProgress},
		opt::Fill{indicator},
		opt::Lead{indicator},
		opt::ForegroundColor{fgColor},
		opt::FontStyles{
			std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};
}

void AntColony::_progressBarTick(indicators::ProgressBar *bar, int n, int total,
								 std::string currentStatus) {
	std::stringstream prefix, postfix;
	prefix << std::setw(3) << (int)std::ceil((double)n / total * 100) << "% ";
	postfix << std::min(n + 1, total) << "/" << total << "  " << currentStatus;

	if (!bar->is_completed()) {
		bar->set_option(indicators::option::PrefixText{prefix.str()});
		bar->set_option(indicators::option::PostfixText{postfix.str()});
		bar->tick();
	}
}
