#include "run.hpp"


void aco::run(Graph *graph, utils::ArgumentParser *args) {
	time_t t;
	srand(time(&t));

    std::cout << "Spawning colony..." << std::endl;
    Colony colony(graph);

    colony.alpha = args->Get<double>("--alpha", colony.alpha);
    colony.beta = args->Get<double>("--beta", colony.beta);
    colony.evaporation = args->Get<double>("--evaporation", colony.evaporation);
    colony.pheromoneConstant = args->Get<double>("--pheromone", colony.pheromoneConstant);
    colony.costConstraint = args->Get<double>("--cost", colony.costConstraint);
    colony.startVertix = args->Get<int>("--start", colony.startVertix);
    colony.antCount = args->Get<int>("--ants", colony.antCount);
    colony.iterations = args->Get<int>("--iterations", colony.iterations);
    colony.bestAntLimit = args->Get<int>("--best_ant_limit", colony.bestAntLimit);
    colony.returnHome = args->Exists("-op");

    Solution best = colony.Solve();

    colony.PrintSolution(best);
}
