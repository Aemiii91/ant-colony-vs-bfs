#include "Colony.hpp"

using namespace aco;

Solution Colony::Solve(int colonyCount) {
	// if only one colony, run this one
	bool run = true;

	if (colonyCount == 1) {
		_solve();
	} else {
		while (run) {
			_progressTotal =
				colonyCount * _params.iterations * _params.antCount;
			auto progressHandler = [this](int n, int total) {
				_progressTick();
			};
			auto start = Clock::now();
			// clone the amount of colonies needed, and solve each of them
			for (int colonyID = 0; colonyID < colonyCount; colonyID++) {
				Colony clone(*this);
				clone.progressHandler = progressHandler;
				clone.solutionHandler = [this, &clone, colonyID](
											double, int, int iteration, int) {
					_assessSolution(clone._bestInColony, iteration, colonyID);
				};
				clone._solve();
				auto current = Clock::now();
				if (!this->_canRunInTime(start, current)) {
					run = false;
					break;
				}
			}
			break;
		}
	}

	return _exportSolution(_bestInColony);
}

bool Colony::_canRunInTime(auto start, auto current) {
	if (this->_params.timeAvailable == 0) return true;

	else if (chrono::duration_cast<std::chrono::seconds>(current - start).count() < this->_params.timeAvailable)
		return true;

	else
		return false;
}

void Colony::_solve() {
	// initialize ants
	std::vector<Ant> ants;
	_initAnts(&ants);

	// set total progress (number of cycles)
	_progressTotal = _params.iterations * _params.antCount;

	for (int iteration = 0; iteration < _params.iterations; iteration++) {
		_runAnts(&ants);

		_matrixData.EvaporatePheromone();

		for (Solution bestInIteration : _pickBestAnts(&ants)) {
			_depositPheromone(bestInIteration);
			_assessSolution(bestInIteration, iteration);
		}

		_resetAnts(&ants);
	}
}

void Colony::_initAnts(std::vector<Ant> *ants) {
	for (int i = 0; i < _params.antCount; i++) {
		ants->push_back(
			Ant(_allVertices, _params.startVertex, &_params, &_matrixData));
	}
}

void Colony::_runAnts(std::vector<Ant> *ants) {
	std::vector<std::future<void>> taskFutures;

	if (_params.threading) {
		for (auto ant = ants->begin(); ant != ants->end(); ++ant) {
			taskFutures.push_back(
				Colony::_threadPool.enqueue(&Ant::Run, &(*ant)));
		}

		for (auto &taskFuture : taskFutures) {
			taskFuture.get();
			_progressTick();
		}
	} else {
		for (auto ant = ants->begin(); ant != ants->end(); ++ant) {
			ant->Run();
			_progressTick();
		}
	}
}

void Colony::_resetAnts(std::vector<Ant> *ants) {
	for (auto ant = ants->begin(); ant != ants->end(); ++ant) {
		ant->Init(_allVertices);
	}
}

bool Colony::_checkAntsComplete(std::vector<Ant> *ants) {
	for (auto ant = ants->begin(); ant != ants->end(); ++ant) {
		if (!ant->isComplete()) {
			return false;
		}
	}
	return true;
}

std::vector<Solution> Colony::_pickBestAnts(std::vector<Ant> *ants) {
	std::vector<Solution> antSolutions;

	// extract all ant solutions
	for (auto itr = ants->begin(); itr != ants->end(); ++itr) {
		antSolutions.push_back(itr->solution());
	}

	// if only one solution needed, return the maximum solution (best)
	if (_params.bestAntLimit == 1) {
		return {*std::max_element(antSolutions.begin(), antSolutions.end())};
	} else if (_params.bestAntLimit > 0) {
		// sort the solution in descending order (better first)
		std::sort(antSolutions.begin(), antSolutions.end(), greater<>());

		// reduce vector to its first n elements
		antSolutions.resize(_params.bestAntLimit);
	}

	return antSolutions;
}

bool Colony::_assessSolution(Solution solution, int iteration, int colonyID) {
	if (!_hasSolution || solution > _bestInColony) {
		_bestInColony = solution;
		_hasSolution = true;
		this->solutionHandler(solution.cost, solution.score, iteration,
							  colonyID);
		return true;
	}
	return false;
}

void Colony::_depositPheromone(Solution antSolution) {
	// calculate quality of the ant (the quality function)
	double deposit = _params.pheromoneConstant / antSolution.cost;

	// deposit pheromone along the ant's route
	for (int i = 0; i < antSolution.route.size() - 1; i++) {
		int fromIndex = antSolution.route[i];
		int toIndex = antSolution.route[i + 1];
		_matrixData.DepositPheromone(fromIndex, toIndex, deposit);
	}
}

Solution Colony::_exportSolution(Solution solution) {
	for (int &index : solution.route) {
		index = (&_graphNodes->at(index))->ID;
	}
	return solution;
}

void Colony::_progressTick() {
	_progressCount = std::min(_progressCount + 1, _progressTotal);

	this->progressHandler(_progressCount, _progressTotal);
}

// initialize the shared thread pool
ThreadPool Colony::_threadPool =
	ThreadPool(std::thread::hardware_concurrency());
