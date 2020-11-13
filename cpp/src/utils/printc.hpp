#ifndef UTILS_PRINT_HPP
#define UTILS_PRINT_HPP
#pragma once

#include <functional>
#include <termcolor/termcolor.hpp>
#include <iostream>
#include <string>

/**
 * A convenience class containing static methods for printing colored output.
 */
class printc {
  public:
	/**
	 * Get or set `colorsEnabled` value.
	 * @param setValue Supply if a value should be set.
	 */
	static bool colorsEnabled(bool setValue = false) {
		static bool colorsEnabled = setValue;
		return colorsEnabled;
	}

	/**
	 * Prints a colored string.
	 * 
	 * @param colorFunc A color function supporting stream.
	 * @param str The string to print.
	 */
	template <typename T1, typename T2>
	static void color(T1 colorFunc, T2 str) {
		if (colorsEnabled()) {
			std::cout << colorFunc << str << termcolor::reset;
		} else {
			std::cout << str;
		}
	}

	/**
	 * Prints a bold colored string (usually brighter).
	 * 
	 * @param colorFunc A color function supporting stream.
	 * @param str The string to print.
	 */
	template <typename T1, typename T2>
	static void boldColor(T1 colorFunc, T2 str) {
		if (colorsEnabled()) {
			std::cout << termcolor::bold << colorFunc << str
					  << termcolor::reset;
		} else {
			std::cout << str;
		}
	}

	/// Print `str` in grey.
	template <typename T> static void grey(T str) {
		color(termcolor::grey, str);
	}
	/// Print `str` in red.
	template <typename T> static void red(T str) {
		color(termcolor::red, str);
	}
	/// Print `str` in green.
	template <typename T> static void green(T str) {
		color(termcolor::green, str);
	}
	/// Print `str` in yellow.
	template <typename T> static void yellow(T str) {
		color(termcolor::yellow, str);
	}
	/// Print `str` in blue.
	template <typename T> static void blue(T str) {
		color(termcolor::blue, str);
	}
	/// Print `str` in magenta.
	template <typename T> static void magenta(T str) {
		color(termcolor::magenta, str);
	}
	/// Print `str` in cyan.
	template <typename T> static void cyan(T str) {
		color(termcolor::cyan, str);
	}
	/// Print `str` in white.
	template <typename T> static void white(T str) {
		color(termcolor::white, str);
	}
	/// Print `str` in bold.
	template <typename T> static void bold(T str) {
		color(termcolor::bold, str);
	}
	/// Print `str` in bold grey.
	template <typename T> static void boldGrey(T str) {
		boldColor(termcolor::grey, str);
	}
	/// Print `str` in bold red.
	template <typename T> static void boldRed(T str) {
		boldColor(termcolor::red, str);
	}
	/// Print `str` in bold green.
	template <typename T> static void boldGreen(T str) {
		boldColor(termcolor::green, str);
	}
	/// Print `str` in bold yellow.
	template <typename T> static void boldYellow(T str) {
		boldColor(termcolor::yellow, str);
	}
	/// Print `str` in bold blue.
	template <typename T> static void boldBlue(T str) {
		boldColor(termcolor::blue, str);
	}
	/// Print `str` in bold magenta.
	template <typename T> static void boldMagenta(T str) {
		boldColor(termcolor::magenta, str);
	}
	/// Print `str` in bold cyan.
	template <typename T> static void boldCyan(T str) {
		boldColor(termcolor::cyan, str);
	}
	/// Print `str` in bold white.
	template <typename T> static void boldWhite(T str) {
		boldColor(termcolor::white, str);
	}
  private:
	// Disallow creating an instance of this object
	printc() {}
};

#endif
