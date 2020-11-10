#ifndef UTILS_VECTOR_HPP
#define UTILS_VECTOR_HPP
#pragma once

#include <vector>
#include <functional>

namespace utils::vector {
    template <typename T, typename Func>
    int match(std::vector<T> *list, Func matchFunc) {
		for (int i = 0; i < list->size(); i++) {
			if (matchFunc(&list->at(i))) {
				return i;
			}
		}
		return -1;
	};

	template <typename T>
	void removeValue(std::vector<T> *list, T value) {
		list->erase(std::remove(list->begin(), list->end(), value), list->end());
	}
}

#endif
