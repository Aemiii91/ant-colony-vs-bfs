#include <vector>
#include <cmath>
#include <algorithm>

namespace aco {
  typedef std::vector<std::vector<double>> MatrixDouble;
  typedef std::vector<int> VertixList;
  typedef std::pair<double, VertixList> Solution;

  class Ant {
    public:
      VertixList route;
      VertixList possibleVertices;
      MatrixDouble costMatrix;
      MatrixDouble pheromoneMatrix;
      MatrixDouble heuristicMatrix;
      double alpha;
      double beta;
      double tourCost = 0.0;
      int initVertix;
      bool runComplete = false;

      /**
       * @param alpha importance of pheromone level
       * @param beta importance of heuristic information
       */
      Ant(int initVertix,
          VertixList allVertices,
          MatrixDouble costMatrix,
          MatrixDouble pheromoneMatrix,
          MatrixDouble heuristicMatrix,
          double alpha, double beta) :
        route(VertixList { initVertix }),
        initVertix(initVertix),
        possibleVertices(allVertices),
        costMatrix(costMatrix),
        pheromoneMatrix(pheromoneMatrix),
        heuristicMatrix(heuristicMatrix),
        alpha(alpha), beta(beta) {
          this->_removeFromVertixList(&(this->possibleVertices), this->initVertix);
        };

      void Reset(VertixList allVertices);
      void Run();
      Solution getSolution() { return Solution(this->tourCost, this->route); };

    private:
      int _pickNextVertix(int currentVertix);
      void _traverse(int fromIndex, int toIndex);
      void _removeFromVertixList(VertixList *vert, int value);
      double _calculateCost();
      double _calculateEdgeProbability(int fromIndex, int toIndex);
      double _calculateMoveProbability(int fromIndex, int toIndex, double norm);
      double _calculateProbabilityNorm(int currentVertix);
  };
}
