#include "run.hpp"

using namespace aco;

void aco::run(Graph *graph, utils::ArgumentParser *args) {
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

	printParameters(colonyCount, params);

	Colony colony(graph, params);

	int totalCycles = colonyCount * params.antCount * params.iterations;
	indicators::ProgressBar bar = createProgressBar(totalCycles);

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
			progressBarTick(&bar, n, total, currentStatus);
		};
	}

	auto start = std::chrono::high_resolution_clock::now();
	Solution bestSolution = colony.Solve(colonyCount);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	if (showProgress) {
		progressBarTick(&bar, totalCycles - 1, totalCycles, currentStatus);
	}

	char s[20];
	snprintf(s, 20, "%.3fs\n", (double)duration.count() / 1000000);
	print::yellow(s);

	std::cout << bestSolution;
}

void aco::printParameters(int colonyCount, Parameters params) {
	if (colonyCount > 1) {
		print::bold(std::to_string(colonyCount) + " colonies");
		print::grey(", ");
	}
	print::bold(std::to_string(params.antCount) + " ants");
	print::grey(", ");
	print::bold(std::to_string(params.iterations) + " iterations");
	print::grey(", ");
	print::grey("[ alpha=");
	print::bold(params.alpha);
	print::grey(", beta=");
	print::bold(params.beta);
	print::grey(", evaporation=");
	print::bold(params.evaporation);
	print::grey(", pheromone=");
	print::bold(params.pheromoneConstant);
	if (params.bestAntLimit != 1) {
		print::grey(", best_ants=");
		print::bold(params.bestAntLimit);
	}
	if (params.startVertex != 0) {
		print::grey(", start=");
		print::bold(params.startVertex);
	}
	if (params.costConstraint != 0) {
		print::grey(", cost=");
		print::bold(params.costConstraint);
	}
	print::grey(" ]\n");
}

indicators::ProgressBar aco::createProgressBar(int maxProgress) {
	namespace opt = indicators::option;
	std::string indicator = "#";
	auto fgColor = print::colorsEnabled() ? indicators::Color::green
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

void aco::progressBarTick(indicators::ProgressBar *bar, int n, int total,
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
