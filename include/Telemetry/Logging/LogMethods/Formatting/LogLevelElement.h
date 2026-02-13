#pragma once
#include "Telemetry/Logging/LogMethods/Formatting/LogFormat.h"

class LogLevelElement : public LogElement {
	public:
	LogLevelElement(LogElementSeperators seperators) : seperator(seperators) {};
	void addElement(std::stringstream& ss, Logger::LogLevel level) override {
		std::string levelStr;
		switch (level) {
		case Logger::LogLevel::DEBUG:
			levelStr = "DEBUG";
			break;
		case Logger::LogLevel::INFO:
			levelStr = "INFO";
			break;
		case Logger::LogLevel::WARN:
			levelStr = "WARN";
			break;
		case Logger::LogLevel::ERROR:
			levelStr = "ERROR";
			break;
		case Logger::LogLevel::CRITICAL:
			levelStr = "CRITICAL";
			break;
		default:
			levelStr = "UNKNOWN";
			break;
		}
		ss << seperateElement(seperator, levelStr);
	}

private:
	LogElementSeperators seperator;
};