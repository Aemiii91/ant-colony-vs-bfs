#ifndef ACO_RUN_HPP
#define ACO_RUN_HPP
#pragma once

#include <iostream>
#include <chrono>
#include <indicators/terminal_size.hpp>
#include <indicators/cursor_control.hpp>
#include <indicators/progress_bar.hpp>

#include "../utils/ArgumentParser.hpp"
#include "../utils/print.hpp"
#include "../graph/graph.h"
#include "Colony.hpp"

namespace aco {
    void run(Graph *graph, utils::ArgumentParser *args);
    indicators::ProgressBar createProgressBar(int maxProgress);
    void progressBarTick(indicators::ProgressBar *bar, int n, int total);
    void printParameters(int colonyCount, Colony *colony);
}

#endif
