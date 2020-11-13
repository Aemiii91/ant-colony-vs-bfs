#include "Ant.hpp"

using namespace aco;

void Ant::Run() {
	int currentVertex = _route.front();
	int nextVertex;

	while (!_possibleVertices.empty()) {
		// pick next vertex based on probabilities
		nextVertex = _pickNextVertex(currentVertex);

		// check if the move can be made
		if (_checkMove(currentVertex, nextVertex)) {
			_traverse(currentVertex, nextVertex);
			currentVertex = nextVertex;
		} else {
			// can't make the move, stop going further
			break;
		}
	}

	// return home if parameter set
	if (_params->returnHome) {
		_traverse(currentVertex, _route.front());
	}

	_runComplete = true;
}

bool Ant::_checkMove(int currentVertex, int nextVertex) {
	if (_params->costConstraint == 0) {
		return true;
	}

	// get the cost of the move
	double moveCost = _matrixData->Cost(currentVertex, nextVertex);

	if (_params->returnHome) {
		// add the cost of getting home
		moveCost += _matrixData->Cost(nextVertex, _route.front());
	}

	return (_cost + moveCost) < _params->costConstraint;
}

int Ant::_pickNextVertex(int currentVertex) {
	double norm = _probabilityNorm(currentVertex);
	std::vector<double> attractiveness =
		_attractivenessVector(currentVertex, norm);
	int choice = _weightedChoice(&attractiveness);
	return _possibleVertices.at(choice);
}

std::vector<double> Ant::_attractivenessVector(int currentVertex, double norm) {
	size_t size = _possibleVertices.size();
	std::vector<double> attractiveness(size, 0.0);

	for (int nextIndex = 0; nextIndex < size; nextIndex++) {
		int nextVertex = _possibleVertices[nextIndex];
		double probability =
			_matrixData->Probability(currentVertex, nextVertex) / norm;
		attractiveness[nextIndex] = probability;
	}

	return attractiveness;
}

int Ant::_weightedChoice(std::vector<double> *attractiveness) {
	auto dist = std::discrete_distribution<int>(attractiveness->begin(),
												attractiveness->end());
	return dist(_random);
}

void Ant::_traverse(int currentVertex, int nextVertex) {
	_route.push_back(nextVertex);
	utils::vector::removeValue(&(_possibleVertices), nextVertex);

	_cost += _matrixData->Cost(currentVertex, nextVertex);
}

double Ant::_probabilityNorm(int currentVertex) {
	double norm = 0.0;
	for (int nextVertex : _possibleVertices) {
		norm += _matrixData->Probability(currentVertex, nextVertex);
	}
	return norm;
}
