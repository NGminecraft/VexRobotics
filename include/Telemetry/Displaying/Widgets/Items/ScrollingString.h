#pragma once
#include "Telemetry/Displaying/ScreenItem.h"
#include <string>

template <size_t N>
class ScrollingString : public ScreenItem {
public:
	ScrollingString(int x, int y) : offsetX(x), offsetY(y) {};

	void addString(const char* str) {
		buffer[currentIndex] = (str != nullptr) ? str : "";
		currentIndex = (currentIndex + 1) % N;
	}

	void print(vex::brain& brain, int x, int y) override {
		for (size_t i = 0; i < N; i++) {
			size_t idx = (currentIndex + i) % N;
			if (!buffer[idx].empty()) {
				brain.Screen.printAt(x + offsetX, y + i + offsetY, buffer[idx].c_str());
			}
		}
	}

	const size_t getBufferSize() const {
		return N;
	}

protected:
	std::string buffer[N];
	size_t currentIndex = 0;

	int offsetX;
	int offsetY;
};