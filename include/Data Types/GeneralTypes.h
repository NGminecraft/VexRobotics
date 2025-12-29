#pragma once
#include <concepts>
#include <type_traits>

template <class T>
concept Numeric = std::is_arithmetic_v<T>;