#include "Colony.hpp"

using namespace aco;

Solution Colony::Solve(int colonyCount) {
	// if only one colony, run this one
	if (colonyCount == 1) {
		return _exportSolution(_solve());
	}

	_progressTotal =
		colonyCount * _params.iterations * _params.antCount;
	auto progressHandler = [this](int n, int total) { _progressTick(); };

	// clone the amount of colonies needed, and solve each of them
	for (int colonyID = 0; colonyID < colonyCount; colonyID++) {
		Colony clone(*this);
		clone.progressHandler = progressHandler;
		clone.solutionHandler = [this, &clone, colonyID](double cost, int score,
														 int iteration, int) {
			if (_assessSolution(clone._solution)) {
				this->solutionHandler(cost, score, iteration, colonyID);
			}
		};
		clone._solve();
	}

	return _exportSolution(_solution);
}

Solution Colony::_solve() {
	ThreadPool pool(std::thread::hardware_concurrency());

	// initialize ants
	std::vector<Ant> ants;
	_initAnts(&ants);

	// set total progress (number of cycles)
	_progressTotal = _params.iterations * _params.antCount;

	for (int iteration = 0; iteration < _params.iterations; iteration++) {
		_runAnts(&pool, &ants);

		_matrixData.EvaporatePheromone();

		for (Solution newSolution : _pickBestAntSolutions(&ants)) {
			_depositPheromone(newSolution);

			if (_assessSolution(newSolution)) {
				this->solutionHandler(newSolution.cost, newSolution.score,
									  iteration, -1);
			}
		}

		_resetAnts(&ants);
	}

	return _solution;
}

void Colony::_initAnts(std::vector<Ant> *ants) {
	for (int i = 0; i < _params.antCount; i++) {
		ants->push_back(
			Ant(_allVertices, &_params, &_matrixData));
	}
}

void Colony::_runAnts(ThreadPool *pool, std::vector<Ant> *ants) {
	for (auto ant = ants->begin(); ant != ants->end(); ++ant) {
		auto job = [this, ant] {
			ant->Run();
			_progressTick();
		};

		if (_params.threading) {
			pool->enqueue(job);
		} else {
			job();
		}
	}

	if (!_params.threading) {
		return;
	}

	while (!_checkAntsComplete(ants)) {
		/* Wait for ants to complete. */
	}
}

void Colony::_resetAnts(std::vector<Ant> *ants) {
	for (auto ant = ants->begin(); ant != ants->end(); ++ant) {
		ant->Init(_allVertices);
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

	if (_params.bestAntLimit == 1) {
		return {*std::max_element(solutions.begin(), solutions.end())};
	}

	std::sort(solutions.begin(), solutions.end(), greater<>());

	if (_params.bestAntLimit > 0) {
		solutions.resize(_params.bestAntLimit);
	}

	return solutions;
}

bool Colony::_assessSolution(Solution solution) {
	if (!_hasSolution || solution > _solution) {
		_solution = solution;
		_hasSolution = true;
		return true;
	}
	return false;
}

void Colony::_depositPheromone(Solution antSolution) {
	// calculate quality of the ant
	double deposit = _params.pheromoneConstant / antSolution.cost;

	for (int i = 0; i < antSolution.route.size() - 1; i++) {
		int fromIndex = antSolution.route[i];
		int toIndex = antSolution.route[i + 1];
		_matrixData.DepositPheromone(fromIndex, toIndex, deposit);
	}
}

void Colony::_progressTick() {
	_progressCount =
		std::min(_progressCount + 1, _progressTotal);

	this->progressHandler(_progressCount, _progressTotal);
}

Solution Colony::_exportSolution(Solution solution) {
	for (int &index : solution.route) {
		index = (&_graphNodes->at(index))->ID;
	}
	return solution;
}
