#include "Telemetry/Logging/LogMethods/Formatting/LogFormat.h"
#include "vex.h"
#include <string>

class LogTimestamp : public LogElement {
public:
	LogTimestamp(LogElementSeperators seperators) : seperator(seperators) {};

	void addElement(std::stringstream& ss) override {
		// It doesn't like std::to_string, so we have to use a stringstream
		std::stringstream temp;
		temp << vex::timer::system();
		ss << seperateElement(seperator, temp.str());
	}

private:
	LogElementSeperators seperator;
};