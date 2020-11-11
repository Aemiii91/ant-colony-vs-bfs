#include "run.hpp"

using namespace aco;

void aco::run(Graph *graph, utils::ArgumentParser *args) {
	time_t t;
	srand(time(&t));

	int colonyCount = 1;
	Parameters params;
	args->Get<int>("--colonies", &colonyCount);
	args->Get<double>("--alpha", &params.alpha);
	args->Get<double>("--beta", &params.beta);
	args->Get<double>("--evaporation", &params.evaporation);
	args->Get<double>("--pheromone", &params.pheromoneConstant);
	args->Get<double>("--cost", &params.costConstraint);
	args->Get<int>("--start", &params.startVertex);
	args->Get<int>("--ants", &params.antCount);
	args->Get<int>("--iterations", &params.iterations);
	args->Get<int>("--best_ants", &params.bestAntLimit);
	params.returnHome = !args->Exists("--noreturn");
	params.threading = !args->Exists("--nothreading");
	bool showProgress = args->Exists("--progress");

	printParameters(colonyCount, params);

	Colony colony(graph, params);

	int totalCycles = colonyCount * params.antCount * params.iterations;
	indicators::ProgressBar bar = createProgressBar(totalCycles);

	if (showProgress) {
		colony.progressHandler = [&bar](int n, int total) {
			progressBarTick(&bar, n, total);
		};
	}

	auto start = std::chrono::high_resolution_clock::now();
	Solution bestSolution = colony.Solve(colonyCount);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	if (showProgress) {
		progressBarTick(&bar, totalCycles, totalCycles);
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

void aco::progressBarTick(indicators::ProgressBar *bar, int n, int total) {
	namespace opt = indicators::option;

	if (!bar->is_completed()) {
		bar->set_option(opt::PrefixText{
			std::to_string((int)std::ceil((double)n / total * 100)) + "% "});
		bar->set_option(
			opt::PostfixText{std::to_string(n) + "/" + std::to_string(total)});
		bar->tick();
	}
}
