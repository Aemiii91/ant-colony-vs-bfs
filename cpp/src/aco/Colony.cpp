#include "Colony.hpp"

using namespace aco;

Solution Colony::Solve(int iterations) {
  Solution currentSolution;
  bool found = false;

  this->_pheromoneMatrix = this->_initPheromoneMatrix();
  this->_heuristicMatrix = this->_initHeuristicMatrix();
    
  std::vector<Ant> ants = this->_initAnts();

  for (int iteration = 0; iteration < iterations; iteration++) {

    for (Ant &ant : ants) {
      ant.Run();
    }

    for (Solution newSolution : this->_pickBestAntSolutions(&ants)) {
      this->_updatePheromoneMatrix(newSolution);

      if (!found || this->_isBetterSolution(newSolution, currentSolution)) {
        currentSolution = newSolution;
        found = true;
      }
    }

    for (Ant &ant : ants) {
      ant.Reset(this->allVertices);
    }

    this->_evaporatePheromoneMatrix();

  }

  return currentSolution;
}

MatrixDouble Colony::_initPheromoneMatrix() {
  int size = this->allVertices.size();
  return MatrixDouble(size, std::vector<double>(size, 1.0));
}

MatrixDouble Colony::_initHeuristicMatrix() {
  int size = this->allVertices.size();
  MatrixDouble heuristicMatrix(size, std::vector<double>(size, 1.0));

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      double cost = this->costMatrix[i][j];

      if (cost > 0) {
        heuristicMatrix[i][j] /= cost;
      }
    }
  }

  return heuristicMatrix;
}

std::vector<Ant> Colony::_initAnts() {
  std::vector<Ant> ants;

  for (int i = 0; i < this->antCount; i++) {
    Ant ant(
      this->startVertix,
      this->allVertices,
      this->costMatrix,
      this->_pheromoneMatrix,
      this->_heuristicMatrix,
      this->alpha,
      this->beta);
    ants.push_back(ant);
  }

  return ants;
}

bool Colony::_isBetterSolution(Solution newSolution, Solution currentSolution) {
  return newSolution.first < currentSolution.first;
}

std::vector<Solution> Colony::_pickBestAntSolutions(std::vector<Ant> *ants, int solutionCount) {
  std::vector<Solution> bestSolutions;

  for (Ant &ant : *ants) {
    Solution newSolution = ant.getSolution();

    if (bestSolutions.size() >= solutionCount) {
      int worstSolutionIndex = this->_findWorstSolution(bestSolutions);

      if (this->_isBetterSolution(newSolution, bestSolutions[worstSolutionIndex])) {
        bestSolutions.erase(bestSolutions.begin() + worstSolutionIndex);
      }
    }
    
    if (bestSolutions.size() < solutionCount) {
      bestSolutions.push_back(newSolution);
    }
  }

  return bestSolutions;
}

int Colony::_findWorstSolution(std::vector<Solution> solutions) {
  int worstIndex = 0;

  if (solutions.size() >= 2) {
    for (int i = 1; i < solutions.size(); i++) {
      if (!this->_isBetterSolution(solutions[i], solutions[worstIndex])) {
        worstIndex = i;
      }
    }
  }

  return worstIndex;
}

void Colony::_updatePheromoneMatrix(Solution antSolution) {
  double cost = antSolution.first;
  VertixList route = antSolution.second;

  for (int i = 0; i < route.size() - 1; i++) {
    int fromIndex = route[i];
    int toIndex = route[i+1];
    double currentLevel = this->_pheromoneMatrix[fromIndex][toIndex];
    double pheromoneLevel = this->pheromoneConstant;

    if (cost > 0) {
      pheromoneLevel /= cost;
    }

    this->_pheromoneMatrix[fromIndex][toIndex] = currentLevel + pheromoneLevel;
  }
}

void Colony::_evaporatePheromoneMatrix() {
  int size = this->_pheromoneMatrix.size();

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      this->_pheromoneMatrix[i][j] *= 1 - this->evaporation;
    }
  }
}
