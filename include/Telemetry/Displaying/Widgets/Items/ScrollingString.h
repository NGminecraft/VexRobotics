#pragma once
#include "Telemetry/Displaying/ScreenItem.h"

template <size_t N>
class ScrollingString : public ScreenItem {
public:
	ScrollingString(int x, int y) : offsetX(x), offsetY(y) {};

	void addString(const char* str) {
		buffer[currentIndex] = str;
		currentIndex = (currentIndex + 1) % N;
	}

	void print(vex::brain& brain, int x, int y) override {
		for (size_t i = 0; i < N; i++) {
			size_t idx = (currentIndex + i) % N;
			if (buffer[idx]) {
				brain.Screen.printAt(x + offSetX, y + i + offsetY, buffer[idx]);
			}
		}
	}

	const size_t getBufferSize() const {
		return N;
	}

protected:
	const char* buffer[N];
	size_t currentIndex = 0;

	int offsetX;
	int offsetY;
};