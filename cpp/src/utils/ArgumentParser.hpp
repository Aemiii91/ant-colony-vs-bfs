#ifndef UTILS_ARGUMENT_PARSER_HPP
#define UTILS_ARGUMENT_PARSER_HPP
#pragma once

#include <string>
#include <vector>

namespace utils {
/**
 * A class that handles parsing of command line arguments.
 */
class ArgumentParser {
  public:
    /**
     * Create an instance of ArgumentParser, and parse `argv`.
     * 
     * @param argc Number of arguments.
     * @param argv Array of arguments.
     */
	ArgumentParser(int &argc, char **argv) {
		for (int i = 1; i < argc; i++) {
			this->_tokens.push_back(std::string(argv[i]));
		}
	}

    /**
     * Gets an argument's value, if it exists, and sets in on valuePointer.
     * 
     * @param option The name of the argument.
     * @param valuePointer A pointer to set the argument value.
     */
	template <class T>
	void Get(const std::string &option, T *valuePointer) const {
		std::vector<std::string>::const_iterator itr;

		itr = std::find(this->_tokens.begin(), this->_tokens.end(), option);

		if (itr != this->_tokens.end() && ++itr != this->_tokens.end()) {
			std::stringstream convert(*itr);
			convert >> *valuePointer;
		}
	}

    /**
     * Check if an option argument is set.
     * 
     * @param option The name of the argument.
     * @return True if option is set.
     */
	bool Exists(const std::string &option) const {
		return std::find(this->_tokens.begin(), this->_tokens.end(), option) !=
			   this->_tokens.end();
	}

  private:
    /// Stores the argument tokens.
	std::vector<std::string> _tokens;
};
} // namespace utils

#endif
