#include "Ant.hpp"

using namespace aco;

void Ant::Run() {
	int currentVertex;
	int nextVertex;

	while (this->_possibleVertices.size()) {
		currentVertex = this->_route[this->_route.size() - 1];
		nextVertex = this->_pickNextVertex(currentVertex);

		double cost = this->_matrixData->Cost(currentVertex, nextVertex);
		double homeCost = 0.0;

		if (this->_params->returnHome) {
			homeCost =
				this->_matrixData->Cost(nextVertex, this->_params->startVertex);
		}

		if (this->_checkConstraint(cost + homeCost)) {
			this->_traverse(currentVertex, nextVertex);
		} else {
			nextVertex = currentVertex;
			break;
		}
	}

	if (this->_params->returnHome) {
		this->_traverse(nextVertex, this->_params->startVertex);
	}

	this->_runComplete = true;
}

void Ant::Reset(std::vector<int> allVertices) {
	this->_runComplete = false;
	this->_cost = 0.0;
	this->_route = std::vector<int>{this->_params->startVertex};
	this->_possibleVertices = allVertices;
	utils::vector::removeValue(&(this->_possibleVertices),
							   this->_params->startVertex);
}

bool Ant::_checkConstraint(double lookahead) {
	return this->_params->costConstraint == 0 ||
		   (this->_cost + lookahead) < this->_params->costConstraint;
}

int Ant::_pickNextVertex(int currentVertex) {
	double norm = this->_calculateProbabilityNorm(currentVertex);
	double highestWeight = 0.0;
	int highestWeightVertex = this->_possibleVertices[0];
	int size = this->_possibleVertices.size();

	std::vector<double> attractiveness(size, 0.0);
	double sum = 0.0;

	for (int nextIndex = 0; nextIndex < size; nextIndex++) {
		double probability = this->_calculateMoveProbability(
			currentVertex, this->_possibleVertices[nextIndex], norm);
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

		if (weight > highestWeight) {
			highestWeightVertex = this->_possibleVertices[nextIndex];
			highestWeight = weight;
		}

		cumulative += weight;
	}

	// no vertex was selected - return vertex with highest probability
	return highestWeightVertex;
}

void Ant::_traverse(int fromIndex, int toIndex) {
	this->_route.push_back(toIndex);
	utils::vector::removeValue(&(this->_possibleVertices), toIndex);

	this->_cost += this->_matrixData->Cost(fromIndex, toIndex);
}

double Ant::_calculateMoveProbability(int fromIndex, int toIndex, double norm) {
	return this->_matrixData->Probability(fromIndex, toIndex) / norm;
}

double Ant::_calculateProbabilityNorm(int currentVertex) {
	double norm = 0.0;
	for (int nextVertex : this->_possibleVertices) {
		norm += this->_matrixData->Probability(currentVertex, nextVertex);
	}
	return norm;
}
