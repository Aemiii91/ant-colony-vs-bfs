#include "Ant.hpp"

using namespace aco;

void Ant::Run() {
	int homeVertex = this->_route[0];
	int currentVertex = homeVertex;
	int nextVertex;

	while (!this->_possibleVertices.empty()) {
		// pick next vertex based on probabilities
		nextVertex = this->_pickNextVertex(currentVertex);

		// get the cost of the move
		double cost = this->_matrixData->Cost(currentVertex, nextVertex);

		if (this->_params->returnHome) {
			// add the cost of getting home
			cost += this->_matrixData->Cost(nextVertex, homeVertex);
		}

		// check if the move can be made
		if (this->_checkConstraint(cost)) {
			this->_traverse(currentVertex, nextVertex);
			currentVertex = nextVertex;
		} else {
			// can't make the move, stop going further
			break;
		}
	}

	// return home if parameter set
	if (this->_params->returnHome) {
		this->_traverse(currentVertex, homeVertex);
	}

	this->_runComplete = true;
}

void Ant::Reset(std::vector<int> allVertices) {
	int startVertex = this->_params->startVertex;
	this->_runComplete = false;
	this->_cost = 0.0;
	this->_route = std::vector<int>{startVertex};
	this->_possibleVertices = allVertices;
	utils::vector::removeValue(&(this->_possibleVertices), startVertex);
}

bool Ant::_checkConstraint(double lookahead) {
	return this->_params->costConstraint == 0 ||
		   (this->_cost + lookahead) < this->_params->costConstraint;
}

int Ant::_pickNextVertex(int currentVertex) {
	size_t size = this->_possibleVertices.size();
	double norm = this->_probabilityNorm(currentVertex);
	double sum = 0.0;
	std::vector<double> attractiveness(size, 0.0);

	// calculate normalized probabilities (attractiveness) and the sum
	for (int nextIndex = 0; nextIndex < size; nextIndex++) {
		int nextVertex = this->_possibleVertices[nextIndex];
		double probability =
			this->_matrixData->Probability(currentVertex, nextVertex) / norm;
		attractiveness[nextIndex] = probability;
		sum += probability;
	}

	// cumulative probability behavior, inspired by:
	// http://stackoverflow.com/a/3679747/5343977
	double randomToss = (rand() / (RAND_MAX + 1.0));
	double cumulative = 0.0;

	for (int nextIndex = 0; nextIndex < size; nextIndex++) {
		double weight = attractiveness[nextIndex] / sum;

		// choose next vertex based on probability
		if (randomToss <= (weight + cumulative)) {
			return this->_possibleVertices[nextIndex];
		}

		cumulative += weight;
	}

	// mathematically impossible to get here
	throw("IMPOSSIBLE: The ant couldn't pick next vertex.");
}

void Ant::_traverse(int currentVertex, int nextVertex) {
	this->_route.push_back(nextVertex);
	utils::vector::removeValue(&(this->_possibleVertices), nextVertex);

	this->_cost += this->_matrixData->Cost(currentVertex, nextVertex);
}

double Ant::_probabilityNorm(int currentVertex) {
	double norm = 0.0;
	for (int nextVertex : this->_possibleVertices) {
		norm += this->_matrixData->Probability(currentVertex, nextVertex);
	}
	return norm;
}
