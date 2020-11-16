#ifndef UTILS_VECTOR_HPP
#define UTILS_VECTOR_HPP
#pragma once

#include <functional>
#include <vector>

/// Helper functions for vectors.
namespace utils::vector {
/**
 * Find the index of an element using a match function.
 *
 * @param list The vector to iterate.
 * @param matchFunc A match function taking an element and returning true if
 * there was a match.
 */
template <typename T, typename Func>
int match(std::vector<T> *list, Func matchFunc) {
	for (int i = 0; i < list->size(); i++) {
		if (matchFunc(&list->at(i))) {
			return i;
		}
	}
	return -1;
};

/**
 * Remove an element from a vector.
 *
 * @param list The vector to remove from.
 * @param value The element to remove.
 */
template <typename T> void removeValue(std::vector<T> *list, T value) {
	list->erase(std::remove(list->begin(), list->end(), value), list->end());
}
} // namespace utils::vector

#endif
