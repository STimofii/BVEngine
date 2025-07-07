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
	BCPPUL_API const std::map<char, char> simple_escapes = {
{'n', '\n'}, {'t', '\t'}, {'r', '\r'}, {'a', '\a'},
{'b', '\b'}, {'f', '\f'}, {'v', '\v'}, {'\\', '\\'},
{'\'', '\''}, {'\"', '\"'}, {'?', '\?'}
	};
	BCPPUL_API std::string parseEscapeSequences(const std::string& input_str);
	BCPPUL_API std::string replaceEscapesWithRaw(const std::string& input_str);
} // namespace bcppul

#endif