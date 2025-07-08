//include/bcppul/properties.h
#pragma once
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>
#include "bcppul/bcppul_expimp.h"
#include "bcppul/string_utils.h"

namespace bcppul {
	class BCPPUL_API Properties {
	private:
		std::string path;
		std::unordered_map<std::string, std::string> map;
	protected:
	public:
		Properties(std::string path = "");
		~Properties();
		void load();
		void load(std::string& text);
		void loadLine(std::string& text);
		friend std::ostream& operator<<(std::ostream& os, Properties& properties);
		std::string get(std::string key, std::string standard_value = "");
		long long getLong(std::string key, long long standard_value = 0);
		double getDouble(std::string key, double standard_value = 0.0);
		bool getBool(std::string key, bool standard_value = false);
		void set(std::string key, std::string value);
		void set(std::string key, long long value);
		void set(std::string key, double value);
		void set(std::string key, bool value);
		void save();
		std::string saveInString();
		std::string& getPath();
		void setPath(std::string path);
	};
}