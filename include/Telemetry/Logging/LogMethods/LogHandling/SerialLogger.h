#pragma once
#include <cstdio>
#include "Telemetry/Logging/LogMethods/LogHandling/LogHandle.h"

class SerialLoggerHandle : public LogHandle {
public:
	SerialLoggerHandle() {};

	void log(const std::string& message) override {
		printf("%s\n", message.c_str());
	}
};