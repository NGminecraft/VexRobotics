#pragma once
#include <sstream>
#include <string>
#include <vector>
#include "Telemetry/Logging/LogMethods/LogHandling/LogHandle.h"
#include "Telemetry/Logging/LogMethods/Formatting/LogFormat.h"

class Logger {
public:
	enum class LogLevel {
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		CRITICAL
	};

	// Get (or create) the singleton instance of the logger
	static Logger& getInstance(const std::string& Name);
	static Logger& getInstance(const std::string& Name, LogLevel defaultLevel);
	static Logger& getInstance();

	// Overloads for const char* for backward compatibility
	static Logger& getInstance(const char* Name) {
		return getInstance(std::string(Name));
	}
	
	static Logger& getInstance(const char* Name, LogLevel defaultLevel) {
		return getInstance(std::string(Name), defaultLevel);
	}

	// Log a message with the default log level
	void log(const std::string& message);

	// Log a message with a specific log level
	void log(const std::string& message, LogLevel level);

	// Overloads for const char* for backward compatibility
	void log(const char* message) {
		log(std::string(message));
	}

	void log(const char* message, LogLevel level) {
		log(std::string(message), level);
	}

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
	Logger(const std::string& Name);
	Logger(const std::string& Name, LogLevel defaultLevel);

	LogLevel defaultLevel;

	std::vector<LogHandle*> simpleHandles;
	std::vector<LogHandle*> handles;

	std::vector<LogElement*> prependedElements;
	std::vector<LogElement*> appendedElements;

	std::string name;
	static Logger* instance;
};