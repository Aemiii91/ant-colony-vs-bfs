#include "Colony.hpp"

using namespace aco;

Colony::Colony(Graph *graph, Parameters params) : _params(params) {
	size_t size = graph->nodelist.size();
	this->_costMatrix =
		utils::vector::initialize2dVector(size, 1.0);

	int index = 0;
	for (Node &node : graph->nodelist) {
		this->_vertexIDs.push_back(node.ID);
		this->_allVertices.push_back(index++);
	}

	for (int i = 0; i < size; i++) {
		Node *node = &graph->nodelist[i];

		int offset = 0;
		for (int j = 0; j < node->edgeList.size(); j++) {
			Edge *edge = &node->edgeList[j];

			if (i == j) {
				offset = 1;
			}

			if (j + offset < size) {
				double cost = edge->weight;
				this->_costMatrix[i][j + offset] = cost > 1.0 ? cost : 1.0;
			}
		}

		this->_costMatrix[i][i] = 0.0;
	}
}

Solution Colony::Solve(int colonyCount) {
	std::vector<Solution> solutions;

	this->_setProgressTotal(colonyCount * this->_params.iterations * this->_params.antCount);

	if (colonyCount == 1) {
		return this->_exportSolution(this->_solve());
	}

	ProgressHandler progressHandler = [this](int n, int total) {
		this->_progressTick();
	};

	for (int i = 0; i < colonyCount; i++) {
		Colony clone(*this);
		clone.progressHandler = progressHandler;

		Solution solution = clone._solve();

		if (!this->_hasSolution ||
			this->_isBetterSolution(solution, this->_solution)) {
			this->_solution = solution;
			this->_hasSolution = true;
		}
	}

	return this->_exportSolution(this->_solution);
}

Solution Colony::_solve() {
	unsigned int threadCount = std::thread::hardware_concurrency();
	ThreadPool pool(threadCount);

	// create default matrices
	this->_initPheromoneMatrix();
	this->_initHeuristicMatrix();

	// initialize ants
	std::vector<Ant> ants;
	this->_initAnts(&ants);

	/// Return true if all ants are done.
	auto checkComplete = [&ants] {
		for (Ant &ant : ants) {
			if (!ant.IsComplete()) {
				return false;
			}
		}
		return true;
	};

	// set total progress (number of cycles)
	this->_setProgressTotal(this->_params.iterations * this->_params.antCount);

	for (int iteration = 0; iteration < this->_params.iterations; iteration++) {
		for (Ant &ant : ants) {
			// add ant to queue
			pool.enqueue([this, &ant] {
				ant.Run();
				this->_progressTick();
			});
		}

		while (!checkComplete()) {
			/* Wait for ants to complete. */
		}

		this->_evaporatePheromoneMatrix();

		for (Solution newSolution : this->_pickBestAntSolutions(&ants)) {
			this->_updatePheromoneMatrix(newSolution);

			if (!this->_hasSolution ||
				this->_isBetterSolution(newSolution, this->_solution)) {
				this->_solution = newSolution;
				this->_hasSolution = true;
			}
		}

		for (Ant &ant : ants) {
			ant.Reset(this->_allVertices);
		}
	}

	return this->_solution;
}

void Colony::_initPheromoneMatrix() {
	this->_pheromoneMatrix =
		utils::vector::initialize2dVector(this->_allVertices.size(), 1.0);
}

void Colony::_initHeuristicMatrix() {
	size_t size = this->_allVertices.size();
	this->_heuristicMatrix = utils::vector::initialize2dVector(size, 1.0);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			double cost = this->_costMatrix[i][j];

			if (cost > 0) {
				this->_heuristicMatrix[i][j] /= cost;
			}
		}
	}
}

void Colony::_initAnts(std::vector<Ant> *ants) {
	for (int i = 0; i < this->_params.antCount; i++) {
		ants->push_back(Ant(this->_params, this->_allVertices,
							&this->_costMatrix, &this->_pheromoneMatrix,
							&this->_heuristicMatrix));
	}
}

std::vector<Solution> Colony::_pickBestAntSolutions(std::vector<Ant> *ants) {
	std::vector<Solution> solutions;

	for (Ant &ant : *ants) {
		Solution newSolution = ant.solution();

		// check if solution limit is reached
		if (solutions.size() >= this->_params.bestAntLimit) {
			int worstIndex = this->_findWorstSolution(solutions);

			if (this->_isBetterSolution(newSolution, solutions[worstIndex])) {
				// remove the worst solution - to make room for the new better
				// solution
				solutions.erase(solutions.begin() + worstIndex);
			}
		}

		if (solutions.size() < this->_params.bestAntLimit) {
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
		if (!this->_isBetterSolution(solutions[i], solutions[worstIndex])) {
			worstIndex = i;
		}
	}

	return worstIndex;
}

bool Colony::_isBetterSolution(Solution newSolution, Solution currentSolution) {
	double newCost = newSolution.cost;
	double currentCost = currentSolution.cost;

	if (this->_params.costConstraint > 0) {
		double newScore = this->_calculateSolutionScore(newSolution);
		double currentScore = this->_calculateSolutionScore(currentSolution);

		return newScore > currentScore ||
			   (newScore == currentScore && newCost < currentCost);
	}

	return newCost < currentCost;
}

double Colony::_calculateSolutionScore(Solution solution) {
	return solution.route.size();
}

void Colony::_updatePheromoneMatrix(Solution antSolution) {
	// calculate quality of the ant
	double pheromone = this->_params.pheromoneConstant / antSolution.cost;

	for (int i = 0; i < antSolution.route.size() - 1; i++) {
		int fromIndex = antSolution.route[i];
		int toIndex = antSolution.route[i + 1];
		double currentLevel = this->_pheromoneMatrix[fromIndex][toIndex];
		this->_pheromoneMatrix[fromIndex][toIndex] = currentLevel + pheromone;
	}
}

void Colony::_evaporatePheromoneMatrix() {
	int size = this->_pheromoneMatrix.size();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			this->_pheromoneMatrix[i][j] *= 1 - this->_params.evaporation;
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

Solution Colony::_exportSolution(Solution solution) {
	for (int &index : solution.route) {
		index = this->_vertexIDs[index];
	}
	return solution;
}
