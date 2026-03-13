#pragma once
#include "DataTypes/Vectors.h"
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <cmath>

template <typename T, size_t ROWS, size_t COLS, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Matrix {
public:
	// CONSTRUCTORS
	Matrix() : data{} {}

	Matrix(std::initializer_list<T> vals) {
		std::copy(vals.begin(), vals.end(), data);
	}

	// FACTORIES

	// Creates an identity matrix
	template<size_t Dummy = ROWS, typename = typename std::enable_if<(Dummy == COLS)>::type>
	static Matrix<T, ROWS, COLS> identity() {
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

	// Sets a column from a vector
	void setColumn(size_t column, const VectorBase<T, ROWS, true>& vec) {
		for (size_t i = 0; i < ROWS; i++) {
			operator()(i, column) = vec[i];
		}
	}
	
	void setColumn(size_t column, const VectorBase<T, ROWS, false>& vec) {
		for (size_t i = 0; i < ROWS; i++) {
			operator()(i, column) = vec[i];
		}
	}

	// Sets a row from a vector
	void setRow(size_t row, const VectorBase<T, COLS, true>& vec) {
		for (size_t i = 0; i < COLS; i++) {
			operator()(row, i) = vec[i];
		}
	}

	void setRow(size_t row, const VectorBase<T, COLS, false>& vec) {
		for (size_t i = 0; i < COLS; i++) {
			operator()(row, i) = vec[i];
		}
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
					sum += operator()(i, k) * mat(k, j);
				}
				result(i, j) = sum;
			}
		}

		return result;
	}

	// Matrix-Vector multiplication
	VectorBase<T, ROWS, true> operator*(const VectorBase<T, ROWS, true>& vec) {
		VectorBase<T, ROWS, true> result;
		for (size_t i = 0; i < ROWS; i++) {
			T sum = 0;
			for (size_t j = 0; j < COLS; j++) {
				sum += operator()(i, j) * vec[j];
			}
			result[i] = sum;
		}
		return result;
	}

	Matrix<T, COLS, ROWS> pseudoInverse() {
		if (ROWS >= COLS) {
			return leftPseudoInverse();
		}
		else {
			return rightPseudoInverse();
		}
	}

	constexpr size_t rows() { return ROWS; };
	constexpr size_t columns() { return COLS; };
private:
	T data[ROWS * COLS];

	// Forward substitution for lower triangular system L*y = b
	template<size_t N>
	Vector<T, N> forwardSubstitution(const Matrix<T, N, N>& L, const Vector<T, N>& b) {
		Vector<T, N> y;
		const T epsilon = static_cast<T>(1e-9);

		for (size_t i = 0; i < N; i++) {
			T sum = T(0);

			for (size_t j = 0; j < i; j++) {
				sum += L(i, j) * y[j];
			}

			T denom = L(i, i);
			if (!std::isfinite(static_cast<double>(denom)) || std::abs(static_cast<double>(denom)) < static_cast<double>(epsilon)) {
				denom = (denom < T(0)) ? -epsilon : epsilon;
			}

			y[i] = (b[i] - sum) / denom;
		}

		return y;
	}

	// Backward substitution for upper triangular system L^T*x = y
	template<size_t N>
	Vector<T, N> backwardSubstitution(const Matrix<T, N, N>& L, const Vector<T, N>& b) {
		Vector<T, N> x;
		const T epsilon = static_cast<T>(1e-9);

		for (int i = N - 1; i >= 0; i--) {
			T sum = T(0);

			for (size_t j = i + 1; j < N; j++) {
				sum += L(j, i) * x[j];
			}

			T denom = L(i, i);
			if (!std::isfinite(static_cast<double>(denom)) || std::abs(static_cast<double>(denom)) < static_cast<double>(epsilon)) {
				denom = (denom < T(0)) ? -epsilon : epsilon;
			}

			x[i] = (b[i] - sum) / denom;
		}
		return x;
	}

	// Cholesky decomposition helper: computes L where M = L*L^T
	template<size_t N>
	void choleskyDecomposition(const Matrix<T, N, N>& M, Matrix<T, N, N>& L) {
		const T epsilon = static_cast<T>(1e-9);
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j <= i; j++) {
				T sum = T(0);

				if (j == i) {
					for (size_t k = 0; k < j; k++) {
						sum += L(j, k) * L(j, k);
					}
					T diag = M(j, j) - sum;
					if (!std::isfinite(static_cast<double>(diag)) || diag < epsilon) {
						diag = epsilon;
					}
					L(j, j) = std::sqrt(diag);
				}
				else {
					for (size_t k = 0; k < j; k++) {
						sum += L(i, k) * L(j, k);
					}
					T denom = L(j, j);
					if (!std::isfinite(static_cast<double>(denom)) || std::abs(static_cast<double>(denom)) < static_cast<double>(epsilon)) {
						denom = epsilon;
					}
					L(i, j) = (M(i, j) - sum) / denom;
				}
			}
		}
	}

	// Solve M*X = I using Cholesky decomposition, where M = L*L^T
	template<size_t N>
	Matrix<T, N, N> solveInverse(const Matrix<T, N, N>& M) {
		Matrix<T, N, N> L;
		choleskyDecomposition(M, L);

		Matrix<T, N, N> M_inv;

		for (size_t col = 0; col < N; col++) {
			Vector<T, N> e;
			e[col] = T(1);

			Vector<T, N> y = forwardSubstitution<N>(L, e);
			Vector<T, N> x = backwardSubstitution<N>(L, y);

			M_inv.setColumn(col, x);
		}

		return M_inv;
	}

	// Left pseudo-inverse: A^+ = (A^T*A)^-1 * A^T (for tall matrices: ROWS >= COLS)
	Matrix<T, COLS, ROWS> leftPseudoInverse() {
		Matrix<T, COLS, COLS> M = transpose() * (*this);
		const T damping = static_cast<T>(1e-6);
		for (size_t i = 0; i < COLS; i++) {
			M(i, i) += damping;
		}
		Matrix<T, COLS, COLS> M_inv = solveInverse<COLS>(M);
		return M_inv * transpose();
	}

	// Right pseudo-inverse: A^+ = A^T * (A*A^T)^-1 (for wide matrices: ROWS < COLS)
	Matrix<T, COLS, ROWS> rightPseudoInverse() {
		Matrix<T, ROWS, ROWS> M = operator*(transpose());
		const T damping = static_cast<T>(1e-6);
		for (size_t i = 0; i < ROWS; i++) {
			M(i, i) += damping;
		}
		Matrix<T, ROWS, ROWS> M_inv = solveInverse<ROWS>(M);
		return transpose() * M_inv;
	}
};
