#pragma once
#include <string>
#include "Telemetry/Logging/LogMethods/Formatting/LogFormat.h"

class LogStringElement : public LogElement {
public:
	LogStringElement(const std::string& str) : text(str), seperator(LogElementSeperators::NONE) {}
	LogStringElement(const std::string& str, LogElementSeperators seperators) : text(str), seperator(seperators) {};
	
	// Overloads for const char* for backward compatibility
	LogStringElement(const char* str) : text(str), seperator(LogElementSeperators::NONE) {}
	LogStringElement(const char* str, LogElementSeperators seperators) : text(str), seperator(seperators) {};
	
	void addElement(std::stringstream& ss) override {
		ss << seperateElement(seperator, text);
	}
private:
	std::string text;
	LogElementSeperators seperator;
};