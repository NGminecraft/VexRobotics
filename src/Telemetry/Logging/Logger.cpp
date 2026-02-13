#include "Telemetry/Logging/Logger.h"
#include <iostream>

Logger* Logger::instance = nullptr;

Logger::Logger(const char* Name) : name(Name), defaultLevel(Logger::LogLevel::DEBUG) {}

Logger::Logger(const char* Name, LogLevel defaultLevel) : name(Name), defaultLevel(defaultLevel) {}

Logger& Logger::getInstance(const char* Name) {
	// FIX 3: Use static instance instead of local variable
	if (instance == nullptr) {
		static Logger logInstance(Name);
		instance = &logInstance;
	}
	return *instance;
}

Logger& Logger::getInstance() {
	if (instance == nullptr) {
		// This is a critical error - getInstance(brain, name) must be called first
		// For embedded systems, we can't throw exceptions, so we need to handle this gracefully
		// You should call the two-parameter version first during initialization
		static Logger defaultInstance("DefaultLogger");
		instance = &defaultInstance;
	}
	return *instance;
}

void Logger::log(const char* msg, Logger::LogLevel level) {
	// Call all the simple handles first
	for (auto handle : simpleHandles) {
		handle->log(msg);
	}

	// Stringstream to build the log message
	std::stringstream ss;
	
	// Prepend elements
	for (auto element : prependedElements) {
		element->addElement(ss, level);
	}

	// Append message
	ss << msg;

	// Append elements
	for (auto element : appendedElements) {
		element->addElement(ss, level);
	}

	// Call handles
	for (auto handle : handles) {
		handle->log(ss.str().c_str());
	}
}

void Logger::log(const char* msg) {
	log(msg, defaultLevel);
}

void Logger::prependElement(LogElement* element) {
	if (element != nullptr) {
		prependedElements.push_back(element);
	}
}

void Logger::appendElement(LogElement* element) {
	if (element != nullptr) {
		appendedElements.push_back(element);
	}
}

void Logger::addSimpleHandle(LogHandle* callback) {
	if (callback != nullptr) {
		simpleHandles.push_back(callback);
	}
}

void Logger::addHandle(LogHandle* handle) {
	if (handle != nullptr) {
		handles.push_back(handle);
	}
}