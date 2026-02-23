#include "Telemetry/Logging/LogMethods/Formatting/LogFormat.h"

std::string seperateElement(LogElementSeperators sep, const std::string text) {
	switch (sep) {
	case LogElementSeperators::SPACE:
		return " " + text + " ";
	case LogElementSeperators::BRACKET:
		return "[" + text + "] ";
	case LogElementSeperators::BRACE:
		return "{" + text + "} ";
	default:
		return text;
	}
}