#ifndef ACO_DATA_HPP
#define ACO_DATA_HPP
#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <indicators/termcolor.hpp>
#include <iostream>
#include <thread>
#include <vector>

namespace aco {
typedef std::vector<std::vector<double>> MatrixDouble;
typedef std::vector<int> VertixList;
typedef std::thread Thread;
typedef std::function<void(int, int)> ProgressHandler;
struct Solution {
	double cost;
	VertixList route;
	friend std::ostream &operator<<(std::ostream &out,
									const Solution &solution) {
		int size = solution.route.size();
		int score =
			solution.route[size - 1] == solution.route[0] ? size - 1 : size;

		out << "( " << termcolor::reset;
		out << termcolor::bold << termcolor::blue << std::floor(solution.cost)
			<< termcolor::reset;
		out << ", ";
		out << termcolor::bold << termcolor::magenta << score
			<< termcolor::reset;
		out << " ) ";
		out << termcolor::grey << "= [";

		for (int i = 0; i < solution.route.size(); i++) {
			if (i > 0) {
				out << ", ";
			}
			out << solution.route[i];
		}

		out << "]\n" << termcolor::reset;

		return out;
	};
};
} // namespace aco

#endif
