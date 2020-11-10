#ifndef ACO_DATA_HPP
#define ACO_DATA_HPP
#pragma once

#include <algorithm>
#include <vector>
#include <thread>
#include <functional>

namespace aco {
    typedef std::vector<std::vector<double>> MatrixDouble;
    typedef std::vector<int> VertixList;
    typedef std::thread Thread;
    typedef std::function<void(int, int)> ProgressHandler;
    struct Solution { double cost; VertixList route; };
}

#endif
