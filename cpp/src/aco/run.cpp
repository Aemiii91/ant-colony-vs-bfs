#include "run.hpp"

using namespace aco;

void aco::run(Graph *graph, utils::ArgumentParser *args) {
	time_t t;
	srand(time(&t));

	// Hide cursor
	indicators::show_console_cursor(false);

	Colony colony(graph);

	int colonies = 1;
	args->Get<int>("--colonies", &colonies);
	args->Get<double>("--alpha", &colony.alpha);
	args->Get<double>("--beta", &colony.beta);
	args->Get<double>("--evaporation", &colony.evaporation);
	args->Get<double>("--pheromone", &colony.pheromoneConstant);
	args->Get<double>("--cost", &colony.costConstraint);
	args->Get<int>("--start", &colony.startVertix);
	args->Get<int>("--ants", &colony.antCount);
	args->Get<int>("--iterations", &colony.iterations);
	args->Get<int>("--best_ants", &colony.bestAntLimit);
	colony.returnHome = !args->Exists("--noreturn");
	colony.threading = !args->Exists("--nothreading");

	bool showProgress = args->Exists("--progress");
	int totalCycles = colonies * colony.antCount * colony.iterations;

	if (colonies > 1) {
		print::bold(std::to_string(colonies) + " colonies");
		print::grey(", ");
	}
	print::bold(std::to_string(colony.antCount) + " ants");
	print::grey(", ");
	print::bold(std::to_string(colony.iterations) + " iterations");
	print::grey(", ");
	print::grey("[ alpha=");
	print::bold(colony.alpha);
	print::grey(", beta=");
	print::bold(colony.beta);
	print::grey(", evaporation=");
	print::bold(colony.evaporation);
	print::grey(", pheromone=");
	print::bold(colony.pheromoneConstant);
	if (colony.bestAntLimit != 1) {
		print::grey(", best_ants=");
		print::bold(colony.bestAntLimit);
	}
	if (colony.startVertix != 0) {
		print::grey(", start=");
		print::bold(colony.startVertix);
	}
	if (colony.costConstraint != 0) {
		print::grey(", cost=");
		print::bold(colony.costConstraint);
	}
	print::grey(" ]\n");

	namespace opt = indicators::option;
	indicators::ProgressBar bar{
		opt::BarWidth{std::max<int>(10, indicators::terminal_width() - 50)},
		opt::ShowElapsedTime{true},
		opt::ShowRemainingTime{true},
		opt::MaxProgress{totalCycles},
		opt::Fill{"#"},
		opt::Lead{"#"},
		opt::ForegroundColor{print::colorsEnabled() ? indicators::Color::green
													: indicators::Color::white},
		opt::FontStyles{
			std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};

	if (showProgress) {
		colony.progressHandler = [&bar](int n, int total) {
			bar.set_option(opt::PrefixText{
				std::to_string((int)std::ceil((double)n / total * 100)) +
				"% "});
			bar.set_option(opt::PostfixText{std::to_string(n) + "/" +
											std::to_string(total)});
			bar.tick();
		};
	}

	auto start = std::chrono::high_resolution_clock::now();
	Solution best = colony.SolveMultiple(colonies);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	bar.set_option(opt::PrefixText{"100% "});
	bar.set_option(opt::PostfixText{std::to_string(totalCycles) + "/" +
									std::to_string(totalCycles)});
	if (!bar.is_completed()) {
		bar.tick();
	}

	char s[20];
	snprintf(s, 20, "%.3fs\n", (double)duration.count() / 1000000);
	print::yellow(s);

	colony.PrintSolution(best);

	// Show cursor
	indicators::show_console_cursor(true);
}
