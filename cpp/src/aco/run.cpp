#include "run.hpp"

using namespace aco;

void aco::run(Graph *graph, utils::ArgumentParser *args) {
	time_t t;
	srand(time(&t));

    std::cout << "Spawning colony..." << std::endl;
    Colony colony(graph);

    int colonies = args->Get<int>("--colonies", 80);

    colony.alpha = args->Get<double>("--alpha", colony.alpha);
    colony.beta = args->Get<double>("--beta", colony.beta);
    colony.evaporation = args->Get<double>("--evaporation", colony.evaporation);
    colony.pheromoneConstant = args->Get<double>("--pheromone", colony.pheromoneConstant);
    colony.costConstraint = args->Get<double>("--cost", colony.costConstraint);
    colony.startVertix = args->Get<int>("--start", colony.startVertix);
    colony.antCount = args->Get<int>("--ants", colony.antCount);
    colony.iterations = args->Get<int>("--iterations", colony.iterations);
    colony.bestAntLimit = args->Get<int>("--best_ant_limit", colony.bestAntLimit);
    colony.returnHome = !args->Exists("--noreturn");

    printf("Solving with %d colonies of %d ants doing %d iterations...\n",
		   colonies, colony.antCount, colony.iterations);
    printf("= %'d cycles\n", colonies * colony.antCount * colony.iterations);
    Solution best = colony.SolveMultiple(colonies);

    printf("Best solution: ");
    colony.PrintSolution(best);
}
