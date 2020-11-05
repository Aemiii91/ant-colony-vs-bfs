#include "Colony.hpp"

using namespace aco;

Colony::Colony(Graph *graph) {
    int matrixSize = graph->nodelist.size();
    this->costMatrix = MatrixDouble(matrixSize, std::vector<double>(matrixSize, 1.0));

    for (Node &node : graph->nodelist) {
		this->allVertices.push_back(node.ID);
    }

	for (int i = 0; i < matrixSize; i++) {
        Node *node = &graph->nodelist[i];

        int offset = 0;
		for (int j = 0; j < node->edgeList.size(); j++) {
            Edge *edge = &node->edgeList[j];

            if (i == j) {
                offset = 1;
            }

            if (j + offset < matrixSize) {
                double cost = edge->weight;
			    this->costMatrix[i][j+offset] = cost > 1.0 ? cost : 1.0;
            }
		}

        this->costMatrix[i][i] = 0.0;
	}
}

Solution Colony::Solve() {
	Solution currentSolution;
	bool found = false;

	this->_pheromoneMatrix = this->_initPheromoneMatrix();
	this->_heuristicMatrix = this->_initHeuristicMatrix();

    std::vector<std::thread> listOfThreads;
	std::vector<Ant> ants = this->_initAnts();

	for (int iteration = 0; iteration < this->iterations; iteration++) {
		for (Ant &ant : ants) {	
			listOfThreads.push_back(ant.Run());	
		}
		
		for (auto& t: listOfThreads){
			t.join();
		}
		
		listOfThreads.clear();

		this->_evaporatePheromoneMatrix();

		for (Solution newSolution : this->_pickBestAntSolutions(&ants)) {
			this->_updatePheromoneMatrix(newSolution);

			if (!found ||
				this->IsBetterSolution(newSolution, currentSolution)) {
				currentSolution = newSolution;
				found = true;
			}
		}

		for (Ant &ant : ants) {
			ant.Reset(this->allVertices);
		}
	}

	return currentSolution;
}

Solution Colony::SolveMultiple(int colonies) {
	Solution best;

	for (int n = 1; n <= colonies; n++) {
		Solution solution = this->Solve();
		if (n == 1 || this->IsBetterSolution(solution, best)) {
			best = solution;
		}
	}

	return best;
}

bool Colony::IsBetterSolution(Solution newSolution, Solution currentSolution) {
	double newCost = newSolution.first;
	double currentCost = currentSolution.first;

	if (this->costConstraint > 0) {
		double newScore = this->_calculateSolutionScore(newSolution);
		double currentScore = this->_calculateSolutionScore(currentSolution);

		return newScore > currentScore ||
			   (newScore == currentScore && newCost < currentCost);
	}

	return newCost < currentCost;
}

void Colony::PrintSolution(Solution solution) {
    double cost = solution.first;
    VertixList route = solution.second;
    int size = route.size();
    double score = route[size - 1] == 0 ? size - 1 : size;

    printf("( %.2f,\t", cost);

    printf("%.1f = [", score);
    for (int i = 0; i < route.size(); i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", route[i]);
    }
    printf("] )\n", score);
}

MatrixDouble Colony::_initPheromoneMatrix() {
	int size = this->allVertices.size();
	return MatrixDouble(size, std::vector<double>(size, 1.0));
}

MatrixDouble Colony::_initHeuristicMatrix() {
	int size = this->allVertices.size();
	MatrixDouble heuristicMatrix(size, std::vector<double>(size, 1.0));

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			double cost = this->costMatrix[i][j];

			if (cost > 0) {
				heuristicMatrix[i][j] /= cost;
			}
		}
	}

	return heuristicMatrix;
}

std::vector<Ant> Colony::_initAnts() {
	std::vector<Ant> ants;

	for (int i = 0; i < this->antCount; i++) {
		Ant ant(this->startVertix, this->allVertices, &this->costMatrix,
				&this->_pheromoneMatrix, &this->_heuristicMatrix, this->alpha,
				this->beta, this->costConstraint, this->returnHome);
		ants.push_back(ant);
	}

	return ants;
}

double Colony::_calculateSolutionScore(Solution solution) {
	return solution.second.size();
}

std::vector<Solution> Colony::_pickBestAntSolutions(std::vector<Ant> *ants) {
	std::vector<Solution> solutions;

	for (Ant &ant : *ants) {
		Solution newSolution = ant.getSolution();

		// check if solution limit is reached
		if (solutions.size() >= this->bestAntLimit) {
			int worstIndex = this->_findWorstSolution(solutions);

			if (this->IsBetterSolution(newSolution, solutions[worstIndex])) {
				// remove the worst solution - to make room for the new better
				// solution
				solutions.erase(solutions.begin() + worstIndex);
			}
		}

		if (solutions.size() < this->bestAntLimit) {
			solutions.push_back(newSolution);
		}
	}

	return solutions;
}

int Colony::_findWorstSolution(std::vector<Solution> solutions) {
	int worstIndex = 0;

	if (solutions.size() == 1) {
		return 0;
	}

	for (int i = 1; i < solutions.size(); i++) {
		if (!this->IsBetterSolution(solutions[i], solutions[worstIndex])) {
			worstIndex = i;
		}
	}

	return worstIndex;
}

void Colony::_updatePheromoneMatrix(Solution antSolution) {
	double cost = antSolution.first;
	VertixList route = antSolution.second;

	for (int i = 0; i < route.size() - 1; i++) {
		int fromIndex = route[i];
		int toIndex = route[i + 1];
		double currentLevel = this->_pheromoneMatrix[fromIndex][toIndex];
		double pheromoneLevel = this->pheromoneConstant;

		pheromoneLevel /= cost;

		this->_pheromoneMatrix[fromIndex][toIndex] =
			currentLevel + pheromoneLevel;
	}
}

void Colony::_evaporatePheromoneMatrix() {
	int size = this->_pheromoneMatrix.size();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			this->_pheromoneMatrix[i][j] *= 1 - this->evaporation;
		}
	}
}
