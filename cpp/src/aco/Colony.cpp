#include "Colony.hpp"

using namespace aco;

Colony::Colony(Graph *graph, Parameters params) : _params(params) {
	size_t size = graph->nodelist.size();
	this->_costMatrix = utils::vector::initialize2dVector(size, 1.0);

	int startVertexIndex = 0;
	int index = 0;
	for (Node &node : graph->nodelist) {
		if (node.ID == this->_params.startVertex) {
			startVertexIndex = index;
		}

		this->_vertexIDs.push_back(node.ID);
		this->_allVertices.push_back(index++);
	}

	// convert startVertex ID to index
	this->_params.startVertex = startVertexIndex;

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

	this->_setProgressTotal(colonyCount * this->_params.iterations *
							this->_params.antCount);

	if (colonyCount == 1) {
		return this->_exportSolution(this->_solve());
	}

	auto progressHandler = [this](int n, int total) { this->_progressTick(); };

	for (int colonyID = 0; colonyID < colonyCount; colonyID++) {
		Colony clone(*this);
		clone.progressHandler = progressHandler;
		clone.solutionHandler = [this, &clone, colonyID](double cost, int score,
														 int iteration, int) {
			if (this->_assessSolution(clone._solution)) {
				this->solutionHandler(cost, score, iteration, colonyID);
			}
		};
		clone._solve();
	}

	return this->_exportSolution(this->_solution);
}

Solution Colony::_solve() {
	ThreadPool pool(std::thread::hardware_concurrency());

	// create default matrices
	this->_initPheromoneMatrix();
	this->_initHeuristicMatrix();

	// initialize ants
	std::vector<Ant> ants;
	this->_initAnts(&ants);

	/// Returns true if all ants are done.
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

			if (this->_assessSolution(newSolution)) {
				this->solutionHandler(newSolution.cost, newSolution.score,
									  iteration, -1);
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

	for (auto itr = ants->begin(); itr != ants->end(); ++itr) {
		solutions.push_back(itr->solution());
	}

	if (this->_params.bestAntLimit == 1) {
		return {*std::max_element(solutions.begin(), solutions.end())};
	}

	std::sort(solutions.begin(), solutions.end(), greater<>());

	if (this->_params.bestAntLimit > 0) {
		solutions.resize(this->_params.bestAntLimit);
	}

	return solutions;
}

bool Colony::_assessSolution(Solution solution) {
	if (!this->_hasSolution || solution > this->_solution) {
		this->_solution = solution;
		this->_hasSolution = true;
		return true;
	}
	return false;
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
