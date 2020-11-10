#include "Colony.hpp"

using namespace aco;

Colony::Colony(Graph *graph) {
	int matrixSize = graph->nodelist.size();
	this->_costMatrix =
		MatrixDouble(matrixSize, std::vector<double>(matrixSize, 1.0));

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
				this->_costMatrix[i][j + offset] = cost > 1.0 ? cost : 1.0;
			}
		}

		this->_costMatrix[i][i] = 0.0;
	}
}

Colony Colony::Clone() const {
	return Colony(*this);
}

Solution Colony::Solve() {
	unsigned int threadCount = std::thread::hardware_concurrency();
	ThreadPool pool(threadCount);

	// create default matrices
	this->_pheromoneMatrix = this->_initPheromoneMatrix();
	this->_heuristicMatrix = this->_initHeuristicMatrix();

	// initialize ants
	std::vector<Ant> ants = this->_initAnts();

	auto checkComplete = [&ants] {
		for (Ant &ant : ants) {
			if (!ant.runComplete) {
				return false;
			}
		}
		return true;
	};

	// set total progress (number of cycles)
	this->_setProgressTotal(this->iterations * this->antCount);

	for (int iteration = 0; iteration < this->iterations; iteration++) {
		for (Ant &ant : ants) {
			// add ant to queue
			pool.enqueue([this, &ant] {
				ant.Run();
				this->_progressTick();
			});
		}

		while (!checkComplete());

		this->_evaporatePheromoneMatrix();

		for (Solution newSolution : this->_pickBestAntSolutions(&ants)) {
			this->_updatePheromoneMatrix(newSolution);

			if (!this->_hasSolution ||
				this->IsBetterSolution(newSolution, this->_solution)) {
				this->_solution = newSolution;
				this->_hasSolution = true;
			}
		}

		for (Ant &ant : ants) {
			ant.Reset(this->allVertices);
		}
	}

	return this->_solution;
}

Solution Colony::SolveMultiple(int colonyCount) {
	std::vector<Solution> solutions;

	this->_setProgressTotal(colonyCount * this->iterations * this->antCount);
	ProgressHandler progressHandler = [this](int n, int total) {
		this->_progressTick();
	};

	for (int i = 0; i < colonyCount; i++) {
		Colony clone = this->Clone();
		clone.progressHandler = progressHandler;
		solutions.push_back(clone.Solve());
	}

	for (Solution &solution : solutions) {
		if (!this->_hasSolution ||
			this->IsBetterSolution(solution, this->_solution)) {
			this->_solution = solution;
			this->_hasSolution = true;
		}
	}

	return this->_solution;
}

bool Colony::IsBetterSolution(Solution newSolution, Solution currentSolution) {
	double newCost = newSolution.cost;
	double currentCost = currentSolution.cost;

	if (this->costConstraint > 0) {
		double newScore = this->_calculateSolutionScore(newSolution);
		double currentScore = this->_calculateSolutionScore(currentSolution);

		return newScore > currentScore ||
			   (newScore == currentScore && newCost < currentCost);
	}

	return newCost < currentCost;
}

void Colony::PrintSolution(Solution solution) {
	int size = solution.route.size();
	int score = solution.route[size - 1] == solution.route[0] ? size - 1 : size;

	print::white("( ");
	print::boldBlue(std::floor(solution.cost));
	print::white(", ");
	print::boldMagenta(score);
	print::white(" ) ");
	print::grey("= [");

	for (int i = 0; i < solution.route.size(); i++) {
		if (i > 0) {
			print::grey(", ");
		}
		print::grey(solution.route[i]);
	}

	print::grey("]\n");
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
			double cost = this->_costMatrix[i][j];

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
		ants.push_back(Ant(this->startVertix, this->allVertices,
						   &this->_costMatrix, &this->_pheromoneMatrix,
						   &this->_heuristicMatrix, this->alpha, this->beta,
						   this->costConstraint, this->returnHome));
	}

	return ants;
}

double Colony::_calculateSolutionScore(Solution solution) {
	return solution.route.size();
}

std::vector<Solution> Colony::_pickBestAntSolutions(std::vector<Ant> *ants) {
	std::vector<Solution> solutions;

	for (Ant &ant : *ants) {
		Solution newSolution = ant.solution();

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
	for (int i = 0; i < antSolution.route.size() - 1; i++) {
		int fromIndex = antSolution.route[i];
		int toIndex = antSolution.route[i + 1];
		double currentLevel = this->_pheromoneMatrix[fromIndex][toIndex];
		double pheromoneLevel = this->pheromoneConstant;

		pheromoneLevel /= antSolution.cost;

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

void Colony::_progressTick(int tickSize) {
	this->_progressCount =
		std::min(this->_progressCount + tickSize, this->_progressTotal);

	this->progressHandler(this->_progressCount, this->_progressTotal);
}

void Colony::_setProgressTotal(int value) {
	this->_progressTotal = value;
}
