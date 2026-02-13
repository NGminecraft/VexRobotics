#pragma once
#include <sstream>

// Base class for log elements, things that add content to a log message
class LogElement {
public:
	virtual void addElement(std::stringstream& ss) = 0;
};