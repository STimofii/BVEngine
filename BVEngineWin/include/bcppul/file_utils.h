//include/bcppul/file_utils.h
#pragma once
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "bcppul/bcppul_expimp.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

namespace bcppul {
	BCPPUL_API std::vector<std::string> getFilesInDirectory(std::string path, bool recursively, std::vector<std::string>& files);
	BCPPUL_API std::vector<std::string> getFilesInDirectory(std::string path, bool recursively = true);
} // namespace bcppul

#endif