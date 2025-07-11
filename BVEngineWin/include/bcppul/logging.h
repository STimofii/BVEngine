#pragma once

#include "bcppul_expimp.h"

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

namespace bcppul {
	BCPPUL_API class Logger;
	BCPPUL_API Logger* getLogger(std::string name, Logger* parent = nullptr);

	BCPPUL_API enum LogLevel {
		TRACE,
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		FATAL,
		NONE
	};
	extern BCPPUL_API std::string log_levels_s[LogLevel::NONE + 1];
	extern BCPPUL_API Logger* logger_root;
	extern BCPPUL_API LogLevel console_log_level;
	extern BCPPUL_API LogLevel file_log_level;
	extern BCPPUL_API std::string logOutFileName;
	extern BCPPUL_API std::ofstream logOutFS;
	extern BCPPUL_API std::unordered_map<std::string, Logger*> loggers;

	BCPPUL_API struct LogRecord {
		Logger* logger;
		LogLevel level;
		const char* message;

		friend std::ostream& operator<<(std::ostream& os, LogRecord& logRecord);
	};
	class BCPPUL_API LogStream {
	private:
		Logger* logger_ptr;
		LogLevel current_level;
		std::stringstream message_stream;

	public:
		LogStream(Logger* logger, LogLevel level);

		LogStream(const LogStream&) = delete;
		LogStream& operator=(const LogStream&) = delete;

		LogStream(LogStream&& other) noexcept
			: logger_ptr(other.logger_ptr),
			current_level(other.current_level),
			message_stream(std::move(other.message_stream)) {
			other.logger_ptr = nullptr;
		}

		LogStream& operator=(LogStream&& other) noexcept {
			if (this != &other) {
				logger_ptr = other.logger_ptr;
				current_level = other.current_level;
				message_stream = std::move(other.message_stream);
				other.logger_ptr = nullptr;
			}
			return *this;
		}

		template<typename T>
		LogStream& operator<<(const T& value) {
			message_stream << value;
			return *this;
		}

		~LogStream();
	};
	BCPPUL_API class Logger {
	private:
	protected:
		std::string name;
		Logger(std::string name, Logger* parent = logger_root);
	public:
		std::string getName();
		void setName(std::string name);

		void BCPPUL_API log(LogRecord& record);
		void BCPPUL_API log(LogLevel level, const char* message);
		void BCPPUL_API trace(const char* message);
		void BCPPUL_API debug(const char* message);
		void BCPPUL_API info(const char* message);
		void BCPPUL_API warning(const char* message);
		void BCPPUL_API error(const char* message);
		void BCPPUL_API fatal(const char* message);
		void BCPPUL_API log(LogLevel level, const std::string& message) {
			log(level, message.c_str());
		}
		void BCPPUL_API trace(const std::string& message) {
			trace(message.c_str());
		}
		void BCPPUL_API debug(const std::string& message) {
			debug(message.c_str());
		}
		void BCPPUL_API info(const std::string& message) {
			info(message.c_str());
		}
		void BCPPUL_API warning(const std::string& message) {
			warning(message.c_str());
		}
		void BCPPUL_API error(const std::string& message) {
			error(message.c_str());
		}
		void BCPPUL_API fatal(const std::string& message) {
			fatal(message.c_str());
		}

		LogStream operator<<(LogLevel level) {
			return LogStream(this, level);
		}

		friend BCPPUL_API Logger* getLogger(std::string name, Logger* parent);
	};

	BCPPUL_API void initLogging();
	BCPPUL_API void finalizationLogging();

	BCPPUL_API void logLogRecord(LogRecord& record);
}