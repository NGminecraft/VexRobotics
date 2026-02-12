#pragma once
#include "Telemetry/Displaying/ScreenItem.h"
#include <tuple>
#include <utility>

template<typename... Args>
class VariableString : public ScreenItem {
public:
    VariableString(const char* format, int x, int y, Args... args)
        : format(format), x(x), y(y), storedArgs(args...) {}

    void print(vex::brain& brain, int xPos, int yPos) override {
        printHelper(brain, xPos, yPos, std::index_sequence_for<Args...>{});
    }

private:
    template<std::size_t... I>
    void printHelper(vex::brain& brain, int xPos, int yPos, std::index_sequence<I...>) {
        brain.Screen.printAt(xPos, yPos, format, std::get<I>(storedArgs)...);
    }

    const char* format;
    int x, y;
    std::tuple<Args...> storedArgs;
};