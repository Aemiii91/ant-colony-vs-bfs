#ifndef ACO_RUN_HPP
#define ACO_RUN_HPP
#pragma once

#include "../utils/ArgumentParser.hpp"
#include "../graph/graph.h"
#include "Colony.hpp"

namespace aco {
    void run(Graph *graph, utils::ArgumentParser *args);
}

#endif
