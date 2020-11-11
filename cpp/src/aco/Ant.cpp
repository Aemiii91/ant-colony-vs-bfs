#include "Ant.hpp"

using namespace aco;

void Ant::Run() {
	int currentVertex;
	int nextVertex;

	while (this->_possibleVertices.size()) {
		currentVertex = this->_route[this->_route.size() - 1];
		nextVertex = this->_pickNextVertex(currentVertex);

		double cost = (*this->_costMatrix)[currentVertex][nextVertex];
		double costHome;

		if (this->_params.returnHome) {
			costHome =
				(*this->_costMatrix)[nextVertex][this->_params.startVertex];
		}

		if (this->_checkConstraint(cost + costHome)) {
			this->_traverse(currentVertex, nextVertex);
		} else {
			nextVertex = currentVertex;
			break;
		}
	}

	if (this->_params.returnHome) {
		this->_traverse(nextVertex, this->_params.startVertex);
	}

	this->_runComplete = true;
}

void Ant::Reset(VertexList allVertices) {
	this->_runComplete = false;
	this->_cost = 0.0;
	this->_route = VertexList{this->_params.startVertex};
	this->_possibleVertices = allVertices;
	utils::vector::removeValue(&(this->_possibleVertices),
							   this->_params.startVertex);
}

bool Ant::_checkConstraint(double lookahead) {
	return this->_params.costConstraint == 0 ||
		   (this->_cost + lookahead) < this->_params.costConstraint;
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
		// double probability = this->_calculateEdgeProbability(currentVertex,
		// this->_possibleVertices[nextIndex]);
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

	this->_cost += (*this->_costMatrix)[fromIndex][toIndex];
}

double Ant::_calculateEdgeProbability(int fromIndex, int toIndex) {
	return std::pow((*this->_pheromoneMatrix)[fromIndex][toIndex],
					this->_params.alpha) *
		   std::pow((*this->_heuristicMatrix)[fromIndex][toIndex],
					this->_params.beta);
}

double Ant::_calculateMoveProbability(int fromIndex, int toIndex, double norm) {
	return _calculateEdgeProbability(fromIndex, toIndex) / norm;
}

double Ant::_calculateProbabilityNorm(int currentVertex) {
	int size = _possibleVertices.size();
	double norm = 0.0;
	for (int nextIndex = 0; nextIndex < size; nextIndex++) {
		norm += _calculateEdgeProbability(currentVertex,
										  this->_possibleVertices[nextIndex]);
	}
	return norm;
}
