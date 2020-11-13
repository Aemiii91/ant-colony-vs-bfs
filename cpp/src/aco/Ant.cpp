#include "Ant.hpp"
#include "random"
#include <ctime>
#include <iterator>
#include <random>
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
		if (nextVertex > 500) {
			std::cout << "The currentVertex = " << currentVertex << " "
					  << " nextVertex:  " << nextVertex << std::endl;
		}
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

template <class PossibleVertices, class Attractiveness, class Generater>
auto weighted_choice( PossibleVertices &pickedVertex, Attractiveness &attract, Generater &gen) {
	auto dist = std::discrete_distribution<int>(std::begin(attract), std::end(attract));
	int index = dist(gen);
	return pickedVertex[index];
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

	int pickedVertex;

        auto g = std::mt19937(std::random_device{}());
        pickedVertex = weighted_choice(this->_possibleVertices, attractiveness, g);

	// cumulative probability behavior, inspired by:
	// http://stackoverflow.com/a/3679747/5343977

	//double randomToss = (rand() / (RAND_MAX + 1.0));
	//double cumulative = 0.0;

        //for (int nextIndex = 0; nextIndex < size; nextIndex++) {
	//	double weight = attractiveness[nextIndex] / sum;

	//	// choose next vertex based on probability
	//	if (randomToss <= (weight + cumulative)) {
	//		pickedVertex = this->_possibleVertices[nextIndex];
	//		break;
	//	}

	//	cumulative += weight;
	//}
	return pickedVertex;
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
