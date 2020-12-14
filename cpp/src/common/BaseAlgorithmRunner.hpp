#ifndef BASE_ALGORITHM_RUNNER_HPP
#define BASE_ALGORITHM_RUNNER_HPP
#pragma once

// include
#include <argparse/argparse.hpp>
// submodules
#include <graph/graph.h>

namespace common {
class BaseAlgorithmRunner {
  public:
	Graph graph;
	int startVertex = 0;
	int iterationLimit = 10000000;
	int costConstraint = 30000;

	virtual void AddArguments(argparse::ArgumentParser *args) = 0;
	virtual void Run(argparse::ArgumentParser *args) = 0;
};
} // namespace common

#endif
