#pragma once
#include "Telemetry/Displaying/ScreenItem.h"
#include <tuple>
#include <utility>

// C++11 compatible index_sequence implementation
template<std::size_t...>
struct index_sequence {};

template<std::size_t N, std::size_t... Seq>
struct make_index_sequence_impl : make_index_sequence_impl<N - 1, N - 1, Seq...> {};

template<std::size_t... Seq>
struct make_index_sequence_impl<0, Seq...> {
    using type = index_sequence<Seq...>;
};

template<std::size_t N>
using make_index_sequence = typename make_index_sequence_impl<N>::type;

template<typename... Args>
using index_sequence_for = make_index_sequence<sizeof...(Args)>;

template<typename... Args>
class VariableString : public ScreenItem {
public:
    VariableString(const char* format, int x, int y, Args... args)
        : format(format), x(x), y(y), storedArgs(args...) {}

    void print(vex::brain& brain, int xPos, int yPos) override {
        printHelper(brain, xPos, yPos, index_sequence_for<Args...>{});
    }

private:
    template<std::size_t... I>
    void printHelper(vex::brain& brain, int xPos, int yPos, index_sequence<I...>) {
        brain.Screen.printAt(xPos, yPos, format, std::get<I>(storedArgs)...);
    }

    const char* format;
    int x, y;
    std::tuple<Args...> storedArgs;
};

// Helper function for template argument deduction (C++11 compatible)
template<typename... Args>
VariableString<Args...>* makeVariableString(const char* format, int x, int y, Args... args) {
    return new VariableString<Args...>(format, x, y, args...);
}