#pragma once
#include "Data Types/GeneralTypes.h"
#include "Data Types/Vectors.h"
#include <cstddef>

template <Numeric T, size_t ROWS, size_t COLS>
class Matrix {
public:
	Matrix() : data{} {}

	requires (ROWS == COLS)
	static Matrix<T, ROWS, COLS> IdentityMatrix() {
		Matrix<T, ROWS, COLS> identity;
		for (size_t i = 0; i < ROWS; ++i) {
			identity[i] = 1;
		}
		return identity;
	}

	Vector<T, COLS>& operator[](size_t index) { return data[index]; }

private:
	Vector<T, COLS> data[ROWS];
};