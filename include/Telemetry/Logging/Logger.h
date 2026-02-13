#pragma once
#include <sstream>
#include <vector>
#include "Telemetry/Logging/LogMethods/LogHandling/LogHandle.h"
#include "Telemetry/Logging/LogMethods/Formatting/LogFormat.h"

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

	void prependElement(LogElement* element);
	void appendElement(LogElement* element);
	
	// Registering a simple handle, or a handle that doesn't contain any formatting elements
	void addSimpleHandle(LogHandle* callback);

	// Registering a handle, something that does stuff with the log message
	void addHandle(LogHandle* handle);

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
private:
	Logger(const char* Name);
	Logger(const char* Name, LogLevel defaultLevel);

	LogLevel defaultLevel;

	std::vector<LogElement*> prependedElements;
	std::vector<LogElement*> appendedElements;

	const char* name;
	static Logger* instance;
};