#ifndef UTILS_PRINT_HPP
#define UTILS_PRINT_HPP
#pragma once

#include <functional>
#include <indicators/termcolor.hpp>
#include <iostream>
#include <string>

class print {
  public:
	static bool colorsEnabled(bool setValue = false) {
		static bool colorsEnabled = setValue;
		return colorsEnabled;
	}

	template <typename T1, typename T2>
	static void color(T1 colorFunc, T2 str) {
		if (colorsEnabled()) {
			std::cout << colorFunc << str << termcolor::reset;
		} else {
			std::cout << str;
		}
	}

	template <typename T1, typename T2>
	static void boldColor(T1 colorFunc, T2 str) {
		if (colorsEnabled()) {
			std::cout << termcolor::bold << colorFunc << str
					  << termcolor::reset;
		} else {
			std::cout << str;
		}
	}

	template <typename T> static void grey(T str) {
		color(termcolor::grey, str);
	}
	template <typename T> static void red(T str) {
		color(termcolor::red, str);
	}
	template <typename T> static void green(T str) {
		color(termcolor::green, str);
	}
	template <typename T> static void yellow(T str) {
		color(termcolor::yellow, str);
	}
	template <typename T> static void blue(T str) {
		color(termcolor::blue, str);
	}
	template <typename T> static void magenta(T str) {
		color(termcolor::magenta, str);
	}
	template <typename T> static void cyan(T str) {
		color(termcolor::cyan, str);
	}
	template <typename T> static void white(T str) {
		color(termcolor::white, str);
	}
	template <typename T> static void bold(T str) {
		color(termcolor::bold, str);
	}
	template <typename T> static void boldGrey(T str) {
		boldColor(termcolor::grey, str);
	}
	template <typename T> static void boldRed(T str) {
		boldColor(termcolor::red, str);
	}
	template <typename T> static void boldGreen(T str) {
		boldColor(termcolor::green, str);
	}
	template <typename T> static void boldYellow(T str) {
		boldColor(termcolor::yellow, str);
	}
	template <typename T> static void boldBlue(T str) {
		boldColor(termcolor::blue, str);
	}
	template <typename T> static void boldMagenta(T str) {
		boldColor(termcolor::magenta, str);
	}
	template <typename T> static void boldCyan(T str) {
		boldColor(termcolor::cyan, str);
	}
	template <typename T> static void boldWhite(T str) {
		boldColor(termcolor::white, str);
	}
};

#endif
