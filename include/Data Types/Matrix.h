#pragma once
#include "Data Types/Vectors.h"
#include <array>
#include <type_traits>

template <typename T, size_t ROWS, size_t COLS>
requires std::is_arithmetic<T>::value
class Matrix {
public:
	// CONSTRUCTORS
	Matrix() : data{} {}

	Matrix(std::initializer_list<T> vals) {
		std::copy(vals.begin(), vals.end(), data);
	}

	// FACTORIES

	// Creates an identity matrix
	static Matrix<T, ROWS, COLS> identity() requires (ROWS == COLS) {
		Matrix<T, ROWS, COLS> mat;
		for (size_t i = 0; i < ROWS; i++) {
			mat(i, i) = T{ 1 };
		}
		return mat;
	}

	// Get the array transpose (warning expensive)
	Matrix<T, COLS, ROWS> transpose() const {
		Matrix<T, COLS, ROWS> transposed;
		for (size_t i = 0; i < COLS; i++) {
			for (size_t j = 0; j < ROWS; j++) {
				transposed(i, j) = operator()(j, i);
			}
		}
		return transposed;
	}

	// Index the array
	T& operator()(size_t r, size_t c) {
		return data[r * COLS + c];
	}

	// Index the array (const)
	const T& operator()(size_t r, size_t c) const {
		return data[r * COLS + c];
	}

	// Gets a row as a non-owning vector
	VectorBase<T, COLS, false> getRow(size_t row) {
		return VectorBase<T, COLS, false>::StridedAccess(&data[row * COLS], 1);
	}

	// Gets a coloumn as a non-owning vector
	VectorBase<T, ROWS, false> getColumn(size_t column) {
		return VectorBase<T, ROWS, false>::StridedAccess(&data[column], COLS);
	}

	// Logic

	// Matrix multiplication, the column size (ROWS) in the first matrix need to equal the row size (COLS) in the other matrix
	template <size_t OTHER_COLUMNS>
	Matrix<T, ROWS, OTHER_COLUMNS> operator*(const Matrix<T, COLS, OTHER_COLUMNS>& mat) const {
		Matrix<T, ROWS, OTHER_COLUMNS> result;

		for (size_t i = 0; i < ROWS; i++) {           // Each row of result
			for (size_t j = 0; j < OTHER_COLUMNS; j++) { // Each column of result
				T sum = 0;
				for (size_t k = 0; k < COLS; k++) {      // Dot product
					sum += (*this)(i, k) * mat(k, j);
				}
				result(i, j) = sum;
			}
		}

		return result;
	}

	constexpr size_t rows() { return ROWS; };
	constexpr size_t columns() { return COLS; };
private:
	T data[ROWS * COLS];
};