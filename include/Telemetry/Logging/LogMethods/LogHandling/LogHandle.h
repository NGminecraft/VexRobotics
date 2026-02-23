#pragma once

// Base class for log handles, things that do stuff with the log messages (print, write to file, etc)
class LogHandle {
public:
	virtual void log(const char* message) = 0;
};