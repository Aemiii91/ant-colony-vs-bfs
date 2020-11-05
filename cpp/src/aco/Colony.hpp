#ifndef ACO_COLONY_HPP
#define ACO_COLONY_HPP
#pragma once

#include "../graph/graph.h"
#include "Ant.hpp"
#include <algorithm>
#include <cmath>
#include <vector>
#include <thread>

namespace aco {
    typedef std::vector<std::vector<double>> MatrixDouble;
    typedef std::vector<int> VertixList;
    typedef std::pair<double, VertixList> Solution;

    class Colony {
    public:
        VertixList allVertices;
        MatrixDouble costMatrix;
        double alpha = 1;
        double beta = 20;
        double evaporation = 0.04;
        double pheromoneConstant = 100.0;
        double costConstraint = 30000;
        int startVertix = 0;
        int antCount = 50;
        int iterations = 80;
        int bestAntLimit = 1;
        bool returnHome = true;

        Colony(std::vector<int> allVertices, MatrixDouble costMatrix)
            : allVertices(allVertices), costMatrix(costMatrix){};
        Colony(Graph *graph);

        Solution Solve();
        Solution SolveMultiple(int colonies = 80);
        bool IsBetterSolution(Solution newSolution, Solution currentSolution);
        void PrintSolution(Solution solution);

    private:
        MatrixDouble _pheromoneMatrix;
        MatrixDouble _heuristicMatrix;
        MatrixDouble _initPheromoneMatrix();
        MatrixDouble _initHeuristicMatrix();
        std::vector<Ant> _initAnts();
        double _calculateSolutionScore(Solution solution);
        std::vector<Solution> _pickBestAntSolutions(std::vector<Ant> *ants);
        int _findWorstSolution(std::vector<Solution> bestSolutions);
        void _updatePheromoneMatrix(Solution bestAntSolution);
        void _evaporatePheromoneMatrix();
    };
} // namespace aco

#endif
