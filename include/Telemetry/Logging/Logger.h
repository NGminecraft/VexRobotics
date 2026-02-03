#pragma once
#include "vex.h"


class Logger {
public:
	static Logger& getInstance(vex::brain& brain, const char* Name);
	static Logger& getInstance();

	void log(const char* message);

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	void clear();

private:
	Logger(vex::brain& brain, const char* Name);
	
	vex::brain& brainRef;
	const char* name;
	static Logger* instance;
};

enum class LogLevel {
	DEBUG,
	INFO,
	WARN,
	ERROR,
	CRITICAL
};