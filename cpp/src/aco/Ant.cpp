#include "Ant.hpp"

using namespace aco;

void Ant::Run() {
	int currentVertix;
	int nextVertix;

	while (this->possibleVertices.size()) {
		currentVertix = this->_route[this->_route.size() - 1];
		nextVertix = this->_pickNextVertix(currentVertix);

		double cost = (*this->costMatrix)[currentVertix][nextVertix];
		double costHome;

		if (this->returnHome) {
			costHome = (*this->costMatrix)[nextVertix][this->startVertix];
		}

		if (this->_checkConstraint(cost + costHome)) {
			this->_traverse(currentVertix, nextVertix);
		} else {
			nextVertix = currentVertix;
			break;
		}
	}

	if (this->returnHome) {
		this->_traverse(nextVertix, this->startVertix);
	}

	this->runComplete = true;
}

void Ant::Reset(VertixList allVertices) {
	this->runComplete = false;
	this->_cost = 0.0;
	this->_route = VertixList{this->startVertix};
	this->possibleVertices = allVertices;
	this->_removeFromVertixList(&(this->possibleVertices), this->startVertix);
}

bool Ant::_checkConstraint(double lookahead) {
	return this->costConstraint == 0 ||
		   (this->_cost + lookahead) < this->costConstraint;
}

int Ant::_pickNextVertix(int currentVertix) {
	double norm = this->_calculateProbabilityNorm(currentVertix);
	double highestWeight = 0.0;
	int highestWeightVertix = this->possibleVertices[0];
	int size = this->possibleVertices.size();

	std::vector<double> attractiveness(size, 0.0);
	double sum = 0.0;

	for (int nextIndex = 0; nextIndex < size; nextIndex++) {
		double probability = this->_calculateMoveProbability(
			currentVertix, this->possibleVertices[nextIndex], norm);
		// double probability = this->_calculateEdgeProbability(currentVertix,
		// this->possibleVertices[nextIndex]);
		attractiveness[nextIndex] = probability;
		sum += probability;
	}

	// cumulative probability behavior, inspired by:
	// http://stackoverflow.com/a/3679747/5343977
	double randomToss = (rand() / (RAND_MAX + 1.0));
	double cumulative = 0.0;

	for (int nextIndex = 0; nextIndex < size; nextIndex++) {
		double weight = attractiveness[nextIndex] / sum;

		// choose next vertix based on probability
		if (randomToss <= (weight + cumulative)) {
			return this->possibleVertices[nextIndex];
		}

		if (weight > highestWeight) {
			highestWeightVertix = this->possibleVertices[nextIndex];
			highestWeight = weight;
		}

		cumulative += weight;
	}

	// no vertix was selected - return vertix with highest probability
	return highestWeightVertix;
}

void Ant::_traverse(int fromIndex, int toIndex) {
	this->_route.push_back(toIndex);
	this->_removeFromVertixList(&(this->possibleVertices), toIndex);

	this->_cost += (*this->costMatrix)[fromIndex][toIndex];
}

void Ant::_removeFromVertixList(VertixList *vert, int value) {
	vert->erase(std::remove(vert->begin(), vert->end(), value), vert->end());
}

double Ant::_calculateEdgeProbability(int fromIndex, int toIndex) {
	return std::pow((*this->pheromoneMatrix)[fromIndex][toIndex], this->alpha) *
		   std::pow((*this->heuristicMatrix)[fromIndex][toIndex], this->beta);
}

double Ant::_calculateMoveProbability(int fromIndex, int toIndex, double norm) {
	return _calculateEdgeProbability(fromIndex, toIndex) / norm;
}

double Ant::_calculateProbabilityNorm(int currentVertix) {
	int size = possibleVertices.size();
	double norm = 0.0;
	for (int nextIndex = 0; nextIndex < size; nextIndex++) {
		norm += _calculateEdgeProbability(currentVertix,
										  this->possibleVertices[nextIndex]);
	}
	return norm;
}
