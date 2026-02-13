#pragma once
#include <sstream>

class Logger {
public:
	enum class LogLevel {
		DEBUG,
		INFO,
		WARN,
		ERROR,
		CRITICAL
	};

	static Logger& getInstance(const char* Name);
	static Logger& getInstance(const char* Name, LogLevel defaultLevel);
	static Logger& getInstance();

	void log(const char* message);
	void log(const char* message, LogLevel level);

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
private:
	Logger(const char* Name);
	Logger(const char* Name, LogLevel defaultLevel);

	LogLevel defaultLevel;

	const char* name;
	static Logger* instance;
};