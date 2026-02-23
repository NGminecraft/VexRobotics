#pragma once
#include "Telemetry/Logging/LogMethods/LogHandling/LogHandle.h"
#include "Telemetry/Displaying/Widgets/Items/ScrollingString.h"

template <size_t N>
class ScrollingStringsHandle : public LogHandle {
public:
	ScrollingStringsHandle(ScrollingString<N>& stringClass) : stringClass(stringClass) {};

	void log(const char* message) override {
		stringClass.addString(message);
	}
protected:
	ScrollingString<N>& stringClass;
};