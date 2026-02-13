#include "Telemetry/Logging/LogMethods/Formatting/LogFormat.h"
#include "vex.h"

class LogTimestamp : public LogElement {
public:
	LogTimestamp(LogElementSeperators seperators) : seperator(seperators) {};

	void addElement(std::stringstream& ss) override {
		ss << seperateElement(seperator, std::to_string(vex::timer::system()));
	}

private:
	LogElementSeperators seperator;
};