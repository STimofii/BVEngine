//include/bcppul/properties.h
#pragma once
#include "bcppul/bcppul_expimp.h"
#include <map>
#include <vector>
#include <iostream>
#include <string>


namespace bcppul {
	class BCPPUL_API Properties {
	private:
		std::string path;
		std::map<std::string, std::string> values;
	protected:
	public:
		Properties(std::string path = "");
		~Properties();
		void load();
		void load(std::string& text);
		void loadLine(std::string& text);
		friend std::ostream& operator<<(std::ostream& os, Properties& properties);

		std::string get(const std::string& key, const std::string& standard_value = std::string(""));
		long long getLong(const std::string& key, const long long standard_value = 0);
		double getDouble(const std::string& key, const double standard_value = 0.0);
		bool getBool(const std::string& key, const bool standard_value = false);
		void set(const std::string& key, const std::string& value);
		void set(const std::string& key, const long long value);
		void set(const std::string& key, const double value);
		void set(const std::string& key, const bool value);

		std::vector<std::string> getArray(const std::string& key);
		std::vector<long long> getLongArray(const std::string& key);
		std::vector<double> getDoubleArray(const std::string& key);
		std::vector<bool> getBoolArray(const std::string& key);
		void setArray(const std::string& key, const std::string* array, const unsigned int len);
		void setArray(const std::string& key, long long* array, const unsigned int len);
		void setArray(const std::string& key, double* array, const unsigned int len);
		void setArray(const std::string& key, bool* array, const unsigned int len);
		void setArray(const std::string& key, const std::vector<std::string>& array);
		void setArray(const std::string& key, const std::vector<long long>& array);
		void setArray(const std::string& key, const std::vector<double>& array);
		void setArray(const std::string& key, const std::vector<bool>& array);

		inline std::string get(const char* key, const char* standard_value = "") {
			return get(std::string(key), std::string(standard_value));
		}
		inline long long getLong(const char* key, const long long standard_value = 0) {
			return getLong(std::string(key), standard_value);
		}
		inline double getDouble(const char* key, const double standard_value = 0.0) {
			return getDouble(std::string(key), standard_value);
		}
		inline bool getBool(const char* key, const bool standard_value = false) {
			return getBool(std::string(key), standard_value);
		}
		inline void set(const char* key, const char* value) {
			set(std::string(key), std::string(value));
		}
		inline void set(const char* key, const long long value) {
			set(std::string(key), value);
		}
		inline void set(const char* key, const double value) {
			set(std::string(key), value);
		}
		inline void set(const char* key, const bool value) {
			set(std::string(key), value);
		}
		inline std::vector<std::string> getArray(const char* key) {
			return getArray(std::string(key));
		}
		inline std::vector<long long> getLongArray(const char* key) {
			return getLongArray(std::string(key));
		}
		inline std::vector<double> getDoubleArray(const char* key) {
			return getDoubleArray(std::string(key));
		}
		inline std::vector<bool> getBoolArray(const char* key) {
			return getBoolArray(std::string(key));
		}
		inline void setArray(const char* key, std::string* array, const unsigned int len) {
			setArray(std::string(key), array, len);
		}
		inline void setArray(const char* key, long long* array, const unsigned int len) {
			setArray(std::string(key), array, len);
		}
		inline void setArray(const char* key, double* array, const unsigned int len) {
			setArray(std::string(key), array, len);
		}
		inline void setArray(const char* key, bool* array, const  unsigned int len) {
			setArray(std::string(key), array, len);
		}
		inline void setArray(const char* key, const std::vector<std::string>& array) {
			setArray(std::string(key), array);
		}
		inline void setArray(const char* key, const std::vector<long long>& array) {
			setArray(std::string(key), array);
		}
		inline void setArray(const char* key, const std::vector<double>& array) {
			setArray(std::string(key), array);
		}
		inline void setArray(const char* key, const std::vector<bool>& array) {
			setArray(std::string(key), array);
		}

		void save();
		std::string saveInString();
		std::string& getPath();
		void setPath(std::string path);
	};
}