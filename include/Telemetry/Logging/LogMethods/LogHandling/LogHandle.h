#pragma once
#include <string>

// Base class for log handles, things that do stuff with the log messages (print, write to file, etc)
class LogHandle {
public:
	virtual void log(const std::string& message) = 0;
};