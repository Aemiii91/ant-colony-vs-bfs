#include "Ant.hpp"

using namespace aco;

void Ant::Reset(VertixList allVertices) {
  this->route = VertixList { this->initVertix };
  this->possibleVertices = allVertices;
  this->_removeFromVertixList(&(this->possibleVertices), this->initVertix);
}

void Ant::Run() {
  this->runComplete = false;

  while (this->possibleVertices.size()) {
    int currentVertix = this->route[this->route.size() - 1];
    int nextVertix = this->_pickNextVertix(currentVertix);
    
    this->_traverse(currentVertix, nextVertix);
  }

  if (this->possibleVertices.size() == 0) {
    this->runComplete = true;
  }
}

int Ant::_pickNextVertix(int currentVertix) {
  double norm = this->_calculateProbabilityNorm(currentVertix);
  double highestProbability = 0.0;
  int vertixHighestProbability = 0;

  for (VertixList::iterator nextVertix = 
       this->possibleVertices.begin();
       nextVertix != this->possibleVertices.end();
       nextVertix++) {
    double probability = this->_calculateMoveProbability(currentVertix, *nextVertix, norm);
    double randomToss = (rand() / (RAND_MAX + 1.0));

    // choose next vertix based on probability
    if (randomToss <= probability) {
      return *nextVertix;
    }

    // keep track of the highest probability
    if (probability > highestProbability) {
      vertixHighestProbability = *nextVertix;
      highestProbability = probability;
    }
  }

  // no vertix was selected - return vertix with highest probability
  return vertixHighestProbability;
}

void Ant::_traverse(int fromIndex, int toIndex) {
  this->route.push_back(toIndex);
  this->_removeFromVertixList(&(this->possibleVertices), toIndex);

  this->tourCost += this->costMatrix[fromIndex][toIndex];
}

void Ant::_removeFromVertixList(VertixList *vert, int value) {
  vert->erase(std::remove(vert->begin(), vert->end(), value), vert->end());
}

double Ant::_calculateEdgeProbability(int fromIndex, int toIndex) {
  return std::pow(this->pheromoneMatrix[fromIndex][toIndex], this->alpha) *
         std::pow(this->heuristicMatrix[fromIndex][toIndex], this->beta);
}

double Ant::_calculateMoveProbability(int fromIndex, int toIndex, double norm) {
  return _calculateEdgeProbability(fromIndex, toIndex) / norm;
}

double Ant::_calculateProbabilityNorm(int currentVertix) {
  int size = possibleVertices.size();
  double norm = 0.0;
  for (auto nextVertix = possibleVertices.begin(); nextVertix != possibleVertices.end(); nextVertix++) {
    norm += _calculateEdgeProbability(currentVertix, *nextVertix);
  }
  return norm;
}
