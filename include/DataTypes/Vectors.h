#pragma once
#include <type_traits>
#include <initializer_list>
#include <array>
#include <cstddef>

// Helper struct for element access (C++11 compatible)
template<bool Owner>
struct VectorElementAccess {
	template<typename T>
	static T& get(std::array<T, 1>& data, size_t i, size_t N) {
		return data[i];
	}
	
	template<typename T>
	static const T& get(const std::array<T, 1>& data, size_t i, size_t N) {
		return data[i];
	}
};

template<>
struct VectorElementAccess<false> {
	template<typename T>
	static T& get(std::array<T*, 1>& data, size_t i, size_t N) {
		return *data[i];
	}
	
	template<typename T>
	static const T& get(const std::array<T*, 1>& data, size_t i, size_t N) {
		return *data[i];
	}
};

template <typename T, size_t N, bool Owner, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
class VectorBase {
public:
	VectorBase() : data{} {};

	// Vector initializer lists
	// Initializes a vector that owns all the data
	template<bool Dummy = Owner, typename = typename std::enable_if<Dummy>::type>
	VectorBase(std::initializer_list<T> values) {
		std::copy(values.begin(), values.end(), data.begin());
	};

	// Initializes a vector that doesn't own the data
	template<bool Dummy = Owner, typename = typename std::enable_if<!Dummy>::type>
	VectorBase(std::initializer_list<T*> values) {
		std::copy(values.begin(), values.end(), data.begin());
	};

	// Variadic implementation for Owner == true
	template <typename... Args, 
		typename = typename std::enable_if<(sizeof...(Args) == N && Owner)>::type>
	VectorBase(Args&&... args) : data{ static_cast<T>(std::forward<Args>(args))... } {}

	// Variadic implementation for Owner == false
	template <typename... Args,
		typename = typename std::enable_if<(sizeof...(Args) == N && !Owner)>::type,
		typename = void>
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

	template<bool Dummy = Owner, typename = typename std::enable_if<!Dummy>::type>
	void setPointer(size_t i, T* ptr) {
		data[i] = ptr;
	}

	T& operator[](size_t i) {
		if (Owner) {
			return data[i];
		}
		else {
			return *data[i];
		}
	}

	const T& operator[](size_t i) const {
		if (Owner) {
			return data[i];
		}
		else {
			return *data[i];
		}
	}

	// Elementwise multiplication
	template <typename Type, size_t Len, bool O, 
		typename = typename std::enable_if<(Len == N && std::is_arithmetic<Type>::value)>::type>
	VectorBase<T, N, Owner>& operator*=(VectorBase<Type, Len, O> vec) {
		for (size_t i = 0; i < N; i++) {
			operator[](i) *= vec[i];
		}
		return *this;
	}

	VectorBase<T, N, true> operator*(const double item) {
		VectorBase<T, N, true> vector;
		for (size_t i = 0; i < N; i++) {
			vector[i] = operator[](i) * item;
		}
		return vector;
	}

	// Cross Prodcut (3D only)
	template<size_t Dummy = N, typename = typename std::enable_if<(Dummy == 3)>::type>
	VectorBase<T, 3, true> cross(VectorBase<T, 3, true> vec) {
		VectorBase<T, 3, true> ret;
		ret[0] = operator[](2) * vec[3] - operator[](3) * vec[2];
		ret[1] = operator[](3) * vec[1] - operator[](1) * vec[3];
		ret[2] = operator[](1) * vec[2] - operator[](2) * vec[1];
		return ret;
	}

	template<size_t Dummy = N, typename = typename std::enable_if<(Dummy == 3)>::type, typename = void>
	VectorBase<T, 3, true> cross(VectorBase<T, 3, false> vec) {
		VectorBase<T, 3, true> ret;
		ret[0] = operator[](2) * vec[3] - operator[](3) * vec[2];
		ret[1] = operator[](3) * vec[1] - operator[](1) * vec[3];
		ret[2] = operator[](1) * vec[2] - operator[](2) * vec[1];
		return ret;
	}

	template <typename Type, size_t Len, bool O,
		typename = typename std::enable_if<(Len == N && std::is_arithmetic<Type>::value)>::type>
	VectorBase<T, N, true> operator*(VectorBase<Type, Len, O> vec) {
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
	std::array<typename std::conditional<Owner, T, T*>::type, N> data;
};

template <typename T, size_t N, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
using Vector = VectorBase<T, N, true>;

template <typename T, size_t N, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
using OwningVector = VectorBase<T, N, true>;

template <typename T, size_t N, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
using PointerVector = VectorBase<T, N, false>;


template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
using Vector2D = Vector<T, 2>;

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
using Vector3D = Vector<T, 3>;

