#pragma once
#include <concepts>
#include <type_traits>

template <class T>
concept Numeric = std::is_arithmetic_v<T>

template <Numeric T, size_t N>
class Vector {
public:
	Vector() : data{} {}

	template <typename ... Args>
	requires (sizeof...(args) == N)
	Vector(args... args) : data{ static_cast<T>(args)... } {}

	T& operator[](size_t index) {
		return data[index];
	}

	const T& operator[](size_t index) const {
		return data[index];
	}

	constexpr size_t size() const { return N; }
private:
	T data[N];
};

template <Numeric T>
using Vector2D = Vector<T, 2>;

template <Numeric T>
using Vector3D = Vector<T, 3>;