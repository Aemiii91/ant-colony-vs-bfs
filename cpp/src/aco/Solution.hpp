#ifndef ACO_SOLUTION_HPP
#define ACO_SOLUTION_HPP
#pragma once

#include <algorithm>
#include <cmath>
#include <indicators/termcolor.hpp>
#include <iostream>

namespace aco {
struct Solution {
  public:
	double cost;
	std::vector<int> route;
	int score;

	Solution() : cost(0.0), route({}), score(0) {};
	Solution(double cost, std::vector<int> route) : cost(cost), route(route), score(_calcScore(&route)) {};

	friend bool operator>(const Solution &a, const Solution &b) {
		return a.score > b.score ||
			   (a.score == b.score && a.cost < b.cost);
	}
	friend bool operator>=(const Solution &a, const Solution &b) {
		return a.score > b.score ||
			   (a.score == b.score && a.cost <= b.cost);
	}
	friend bool operator<(const Solution &a, const Solution &b) {
		return a.score < b.score ||
			   (a.score == b.score && a.cost > b.cost);
	}
	friend bool operator<=(const Solution &a, const Solution &b) {
		return a.score < b.score ||
			   (a.score == b.score && a.cost >= b.cost);
	}

	friend std::ostream &operator<<(std::ostream &out, const Solution &solution) {
		out << "( " << termcolor::reset;
		out << termcolor::bold << termcolor::blue << std::floor(solution.cost)
			<< termcolor::reset;
		out << ", ";
		out << termcolor::bold << termcolor::magenta << solution.score
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

  private:
	int _calcScore(std::vector<int> *route) {
		size_t size = route->size();
		return route->at(size - 1) == route->at(0) ? size - 1 : size;
	};
};
}

#endif
