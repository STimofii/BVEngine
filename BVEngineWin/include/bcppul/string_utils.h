//include/bcppul/string_utils.h
#pragma once
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "bcppul/bcppul_expimp.h"
#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include "bcppul/timer.h"
#include "bcppul/file_utils.h"

namespace bcppul {
	const std::map<char, char> simple_escapes = {
{'n', '\n'}, {'t', '\t'}, {'r', '\r'}, {'a', '\a'},
{'b', '\b'}, {'f', '\f'}, {'v', '\v'}, {'\\', '\\'},
{'\'', '\''}, {'\"', '\"'}, {'?', '\?'}
	};
	BCPPUL_API std::string parseEscapeSequences(const std::string& input_str);
	BCPPUL_API std::string replaceEscapesWithRaw(const std::string& input_str);
	BCPPUL_API size_t findXOf(std::string& str, char c, size_t x);
	BCPPUL_API std::string& ltrim(std::string& s);
	BCPPUL_API std::string& rtrim(std::string& s);
    BCPPUL_API std::string& trim(std::string& s);
} // namespace bcppul

#endif