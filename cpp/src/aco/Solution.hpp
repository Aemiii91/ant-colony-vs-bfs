#ifndef ACO_SOLUTION_HPP
#define ACO_SOLUTION_HPP
#pragma once
// std
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
// include
#include <termcolor/termcolor.hpp>

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

	/// Comparison implementation
	bool operator==(const Solution &other) {
		return this->score == other.score && this->cost == other.cost;
	}
	/// A better solution is "greater than" a worse solution.
	bool operator>(const Solution &other) {
		return this->score > other.score ||
			   (this->score == other.score && this->cost < other.cost);
	}
	bool operator>=(const Solution &other) {
		return *this > other || *this == other;
	}
	bool operator<(const Solution &other) {
		return !(*this >= other);
	}
	bool operator<=(const Solution &other) {
		return !(*this > other);
	}

	/// Stream operator implementation
	friend std::ostream &operator<<(std::ostream &out,
									const Solution &solution) {
		out << "( " << termcolor::reset;
		out << termcolor::bold << termcolor::blue << std::floor(solution.cost)
			<< termcolor::reset;
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

		out << "]" << termcolor::reset << std::endl;

		return out;
	};

  private:
	/**
	 * Calculates the solution's score, based on the route.
	 *
	 * @param route A pointer to the solution's route.
	 * @return The solution's score.
	 */
	int _calcScore(std::vector<int> *route) {
		size_t size = route->size();
		return size > 0 && route->front() == route->back() ? size - 1 : size;
	};
};
} // namespace aco

#endif
