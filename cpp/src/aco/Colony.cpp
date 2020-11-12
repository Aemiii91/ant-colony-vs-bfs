#include "Colony.hpp"

using namespace aco;

Colony::Colony(Graph *graph, Parameters params) : _params(params) {
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

	// initialize the matrices
	this->_matrixData = MatrixData(this->_vertexIDs, graph, &this->_params);
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

	// initialize ants
	std::vector<Ant> ants;
	this->_initAnts(&ants);

	// set total progress (number of cycles)
	this->_setProgressTotal(this->_params.iterations * this->_params.antCount);

	for (int iteration = 0; iteration < this->_params.iterations; iteration++) {
		this->_runAnts(&pool, &ants);

		this->_matrixData.EvaporatePheromone();

		for (Solution newSolution : this->_pickBestAntSolutions(&ants)) {
			this->_depositPheromone(newSolution);

			if (this->_assessSolution(newSolution)) {
				this->solutionHandler(newSolution.cost, newSolution.score,
									  iteration, -1);
			}
		}

		this->_resetAnts(&ants);
	}

	return this->_solution;
}

void Colony::_initAnts(std::vector<Ant> *ants) {
	for (int i = 0; i < this->_params.antCount; i++) {
		ants->push_back(
			Ant(this->_allVertices, &this->_params, &this->_matrixData));
	}
}

void Colony::_runAnts(ThreadPool *pool, std::vector<Ant> *ants) {
	for (auto ant = ants->begin(); ant != ants->end(); ++ant) {
		auto job = [this, ant] {
			ant->Run();
			this->_progressTick();
		};

		if (this->_params.threading) {
			pool->enqueue(job);
		} else {
			job();
		}
	}

	if (!this->_params.threading) {
		return;
	}

	while (!this->_checkAntsComplete(ants)) {
		/* Wait for ants to complete. */
	}
}

void Colony::_resetAnts(std::vector<Ant> *ants) {
	for (auto ant = ants->begin(); ant != ants->end(); ++ant) {
		ant->Reset(this->_allVertices);
	}
}

bool Colony::_checkAntsComplete(std::vector<Ant> *ants) {
	for (auto ant = ants->begin(); ant != ants->end(); ++ant) {
		if (!ant->IsComplete()) {
			return false;
		}
	}
	return true;
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

void Colony::_depositPheromone(Solution antSolution) {
	// calculate quality of the ant
	double deposit = this->_params.pheromoneConstant / antSolution.cost;

	for (int i = 0; i < antSolution.route.size() - 1; i++) {
		int fromIndex = antSolution.route[i];
		int toIndex = antSolution.route[i + 1];
		this->_matrixData.DepositPheromone(fromIndex, toIndex, deposit);
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
