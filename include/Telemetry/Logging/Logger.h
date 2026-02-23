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

	// Get (or create) the singleton instance of the logger
	static Logger& getInstance(const char* Name);
	static Logger& getInstance(const char* Name, LogLevel defaultLevel);
	static Logger& getInstance();

	// Log a message with the default log level
	void log(const char* message);

	// Log a message with a specific log level
	void log(const char* message, LogLevel level);


	// Add an element to the beginning of a log message
	void prependElement(LogElement* element);

	// Add an element to the end of a log message
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

	std::vector<LogHandle*> simpleHandles;
	std::vector<LogHandle*> handles;

	std::vector<LogElement*> prependedElements;
	std::vector<LogElement*> appendedElements;

	const char* name;
	static Logger* instance;
};