#pragma once
#include "Telemetry/Logging/LogMethods/Formatting/LogFormat.h"

class LogStringElement : public LogElement {
public:
	LogStringElement(const char* str) : text(str), seperator(LogElementSeperators::NONE) {}
	LogStringElement(const char* str, LogElementSeperators seperators) : text(str), seperator(seperators) {};
	void addElement(std::stringstream& ss) override {
		ss << seperateElement(seperator, text);
	}
private:
	const char* text;
	LogElementSeperators seperator;
}