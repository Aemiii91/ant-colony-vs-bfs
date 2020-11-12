#ifndef ACO_SOLUTION_HPP
#define ACO_SOLUTION_HPP
#pragma once
// std
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
// include
#include <indicators/termcolor.hpp>
// submodules
#include <utils/printc.hpp>

namespace aco {
/**
 * A Solution struct containing the solution's cost, route, and score.
 */
struct Solution {
  public:
	/// The solution's cost.
	double cost;
	/// The solution's route.
	std::vector<int> route;
	/// The solution's score.
	int score;

	/**
	 * Constructs a `Solution` object containing the solution's cost, route, and
	 * score (the score is calculated based on the route).
	 *
	 * @param cost The solution's cost.
	 * @param route The solution's route.
	 */
	Solution(double cost, std::vector<int> route)
		: cost(cost), route(route), score(_calcScore(&this->route)){};
	/// Default constructor.
	Solution() : cost(0.0), route({}), score(0){};

	/**
	 * Comparison implementation: A better solution is greater than a worse
	 * solution.
	 */
	friend bool operator>(const Solution &a, const Solution &b) {
		return a.score > b.score || (a.score == b.score && a.cost < b.cost);
	}
	/**
	 * Comparison implementation: A better solution is greater than or equal to
	 * a worse solution.
	 */
	friend bool operator>=(const Solution &a, const Solution &b) {
		return a.score > b.score || (a.score == b.score && a.cost <= b.cost);
	}
	/**
	 * Comparison implementation: A worse solution is less than a better
	 * solution.
	 */
	friend bool operator<(const Solution &a, const Solution &b) {
		return a.score < b.score || (a.score == b.score && a.cost > b.cost);
	}
	/**
	 * Comparison implementation: A worse solution is less than or equal to a
	 * better solution.
	 */
	friend bool operator<=(const Solution &a, const Solution &b) {
		return a.score < b.score || (a.score == b.score && a.cost >= b.cost);
	}

	/// Stream operator implementation
	friend std::ostream &operator<<(std::ostream &out,
									const Solution &solution) {
		if (printc::colorsEnabled()) {
			out << "( " << termcolor::reset;
			out << termcolor::bold << termcolor::blue
				<< std::floor(solution.cost) << termcolor::reset;
			out << ", ";
			out << termcolor::bold << termcolor::magenta << solution.score
				<< termcolor::reset;
			out << " )" << std::endl;

			out << termcolor::grey << "[";

			for (int i = 0; i < solution.route.size(); i++) {
				if (i > 0) {
					out << ", ";
				}
				out << solution.route[i];
			}

			out << "]\n" << termcolor::reset;
		} else {
			out << "( " << std::floor(solution.cost) << ", " << solution.score
				<< " )" << std::endl;

			out << "[";
			for (int i = 0; i < solution.route.size(); i++) {
				if (i > 0) {
					out << ", ";
				}
				out << solution.route[i];
			}
			out << "]\n";
		}

		return out;
	};

  private:
	/**
	 * Calculates the solution's score, based on the route.
	 *
	 * @param route A pointer to the solution's route.
	 */
	int _calcScore(std::vector<int> *route) {
		size_t size = route->size();
		return route->at(size - 1) == route->at(0) ? size - 1 : size;
	};
};
} // namespace aco

#endif
