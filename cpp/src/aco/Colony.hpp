#ifndef ACO_COLONY_HPP
#define ACO_COLONY_HPP
#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include "Ant.hpp"

namespace aco {
  typedef std::vector<std::vector<double>> MatrixDouble;
  typedef std::vector<int> VertixList;
  typedef std::pair<double, VertixList> Solution;

  class Colony {
    public:
      VertixList allVertices;
      MatrixDouble costMatrix;
      double alpha = 0.5;
      double beta = 1.2;
      double evaporation = 0.4;
      double pheromoneConstant = 1000.0;
      int startVertix = 0;
      int antCount = 50;

      Colony(std::vector<int> allVertices, MatrixDouble costMatrix) :
        allVertices(allVertices), costMatrix(costMatrix) { };

      Solution Solve(int iterations = 80);

    private:
      MatrixDouble _pheromoneMatrix;
      MatrixDouble _heuristicMatrix;
      MatrixDouble _initPheromoneMatrix();
      MatrixDouble _initHeuristicMatrix();
      std::vector<Ant> _initAnts();
      bool _isBetterSolution(Solution newSolution, Solution currentSolution);
      std::vector<Solution> _pickBestAntSolutions(std::vector<Ant> *ants, int solutionCount = 10);
      int _findWorstSolution(std::vector<Solution> bestSolutions);
      void _updatePheromoneMatrix(Solution bestAntSolution);
      void _evaporatePheromoneMatrix();
  };
}

#endif
