#pragma once
#include <type_traits>
#include <initializer_list>
#include <array>

template <typename T, size_t N, bool Owner>
	requires std::is_arithmetic<T>::value
class VectorBase {
public:
	VectorBase() : data{} {};

	// Vector initializer lists
	// Initializes a vector that owns all the data
	VectorBase(std::initializer_list<T> values) requires (Owner) {
		std::copy(values.begin(), values.end(), data.begin());
	};

	// Initializes a vector that doesn't own the data
	VectorBase(std::initializer_list<T*> values) requires (!Owner) {
		std::copy(values.begin(), values.end(), data.begin());
	};

	// Variadic implementation for Owner == true
	template <typename... Args>
		requires (sizeof...(Args) == N && Owner)
	VectorBase(Args&&... args) : data{ static_cast<T>(std::forward<Args>(args))... } {}

	// Variadic implementation for Owner == false
	template <typename... Args>
		requires (sizeof...(Args) == N && !Owner)
	VectorBase(Args&&... args) : data{ std::forward<Args>(args)... } {}

	// FACTORIES

	// Builds Vector across a strided block of memory (e.g. matrix row) using a start and stride length
	static VectorBase<T, N, false> StridedAccess(T* start, size_t stride) {
		VectorBase<T, N, false> vec;
		for (size_t i = 0; i < N; i++) {
			vec.setPointer(i, start + i * stride);
		}
		return vec;
	}

	void setPointer(size_t i, T* ptr) requires (!Owner) {
		data[i] = ptr;
	}

	T& operator[](size_t i) {
		if constexpr (Owner) {
			return data[i];
		}
		else {
			return *data[i];
		}
	}

	const T& operator[](size_t i) const {
		if constexpr (Owner) {
			return data[i];
		}
		else {
			return *data[i];
		}
	}

	// Elementwise multiplication
	template <typename Type, size_t Len, bool O>
	VectorBase<T, N, Owner>& operator*=(VectorBase<Type, Len, O> vec) requires (Len == N && std::is_arithmetic<Type>::value) {
		for (size_t i = 0; i < N; i++) {
			operator[](i) *= vec[i];
		}
		return *this;
	}

	template <typename Type, size_t Len, bool O>
	VectorBase<T, N, true> operator*(VectorBase<Type, Len, O> vec) requires (Len == N && std::is_arithmetic<Type>::value) {
		VectorBase<T, N, true> ret;
		for (size_t i = 0; i < N; i++) {
			ret[i] = operator[](i) * vec[i];
		}
		return ret;
	}

	const T sum() const {
		T sum{ 0 };
		for (size_t i = 0; i < N; i++) {
			sum += operator[](i);
		}
		return sum;
	}



	constexpr size_t size() const { return N; }
private:
	std::array<std::conditional_t<Owner, T, T*>, N> data;
};

template <typename T, size_t N>
	requires std::is_arithmetic<T>::value
using Vector = VectorBase<T, N, true>;

template <typename T, size_t N>
	requires std::is_arithmetic<T>::value
using OwningVector = VectorBase<T, N, true>;

template <typename T, size_t N>
	requires std::is_arithmetic<T>::value
using PointerVector = VectorBase<T, N, false>;


template <typename T>
	requires std::is_arithmetic<T>::value
using Vector2D = Vector<T, 2>;

template <typename T>
	requires std::is_arithmetic<T>::value
using Vector3D = Vector<T, 3>;
