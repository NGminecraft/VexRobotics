#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "../../include/DataTypes/Vectors.h"
#include "../../include/DataTypes/Matrix.h"

// Test counter
int tests_passed = 0;
int tests_failed = 0;

// Helper function to print a vector
template<typename T, size_t N>
void printVector(const VectorBase<T, N, true>& vec, const std::string& name) {
    std::cout << name << ": [";
    for (size_t i = 0; i < N; ++i) {
        std::cout << std::setw(8) << std::setprecision(4) << vec[i];
        if (i < N - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Helper function to print a matrix
template<typename T, size_t ROWS, size_t COLS>
void printMatrix(const Matrix<T, ROWS, COLS>& mat, const std::string& name) {
    std::cout << name << " (" << ROWS << "x" << COLS << "):" << std::endl;
    for (size_t i = 0; i < ROWS; ++i) {
        std::cout << "  [";
        for (size_t j = 0; j < COLS; ++j) {
            std::cout << std::setw(8) << std::setprecision(4) << mat(i, j);
            if (j < COLS - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

// Test assertion helper
template<typename T>
void assert_equals(const T& actual, const T& expected, const std::string& test_name) {
    if (std::abs(actual - expected) < 1e-6) {
        std::cout << "[PASS] " << test_name << std::endl;
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << " - Expected: " << expected << ", Got: " << actual << std::endl;
        tests_failed++;
    }
}

void assert_true(bool condition, const std::string& test_name) {
    if (condition) {
        std::cout << "[PASS] " << test_name << std::endl;
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        tests_failed++;
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "      VECTOR OPERATIONS TEST" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // Test Vector creation
    Vector<double, 3> v1 = {1.0, 2.0, 3.0};
    Vector<double, 3> v2 = {4.0, 5.0, 6.0};
    
    printVector(v1, "v1");
    printVector(v2, "v2");
    std::cout << std::endl;
    
    // Test scalar multiplication
    auto v3 = v1 * 2.0;
    printVector(v3, "v1 * 2.0");
    assert_equals(v3[0], 2.0, "Scalar multiplication index 0");
    assert_equals(v3[1], 4.0, "Scalar multiplication index 1");
    assert_equals(v3[2], 6.0, "Scalar multiplication index 2");
    
    // Test elementwise multiplication
    auto v4 = v1 * v2;
    printVector(v4, "v1 * v2 (elementwise)");
    assert_equals(v4[0], 4.0, "Elementwise multiplication index 0");
    assert_equals(v4[1], 10.0, "Elementwise multiplication index 1");
    assert_equals(v4[2], 18.0, "Elementwise multiplication index 2");
    
    // Test cross product
    auto v5 = v1.cross(v2);
    printVector(v5, "v1 x v2 (cross product)");
    assert_equals(v5[0], -3.0, "Cross product index 0");
    assert_equals(v5[1], 6.0, "Cross product index 1");
    assert_equals(v5[2], -3.0, "Cross product index 2");
    
    // Test sum
    double v1_sum = v1.sum();
    std::cout << "Sum of v1: " << v1_sum << std::endl;
    assert_equals(v1_sum, 6.0, "Vector sum");
    std::cout << std::endl;
    
    std::cout << "========================================" << std::endl;
    std::cout << "      MATRIX OPERATIONS TEST" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // Test Matrix creation
    Matrix<double, 3, 3> m1 = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };
    printMatrix(m1, "m1");
    std::cout << std::endl;
    
    // Test identity matrix
    auto identity = Matrix<double, 3, 3>::identity();
    printMatrix(identity, "Identity Matrix");
    std::cout << std::endl;
    
    // Test matrix transpose
    auto m1_transposed = m1.transpose();
    printMatrix(m1_transposed, "m1 Transposed");
    std::cout << std::endl;
    
    // Test matrix multiplication (square matrices)
    Matrix<double, 3, 3> m2 = {
        2.0, 0.0, 1.0,
        1.0, 3.0, 2.0,
        0.0, 1.0, 4.0
    };
    printMatrix(m2, "m2");
    std::cout << std::endl;
    
    auto m3 = m1 * m2;
    printMatrix(m3, "m1 * m2");
    std::cout << std::endl;
    
    // Test matrix multiplication (non-square matrices)
    Matrix<double, 2, 3> m4 = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0
    };
    
    Matrix<double, 3, 2> m5 = {
        7.0,  8.0,
        9.0, 10.0,
        11.0, 12.0
    };
    
    printMatrix(m4, "m4 (2x3)");
    std::cout << std::endl;
    printMatrix(m5, "m5 (3x2)");
    std::cout << std::endl;
    
    auto m6 = m4 * m5;
    printMatrix(m6, "m4 * m5 (2x2 result)");
    std::cout << std::endl;
    
    std::cout << "========================================" << std::endl;
    std::cout << "   MATRIX-VECTOR OPERATIONS TEST" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // Test matrix-vector multiplication
    Vector<double, 3> vec = {1.0, 2.0, 3.0};
    printMatrix(m2, "m2");
    std::cout << std::endl;
    printVector(vec, "vec");
    
    auto result_vec = m2 * vec;
    printVector(result_vec, "m2 * vec");
    std::cout << std::endl;
    
    // Test row and column access
    std::cout << "========================================" << std::endl;
    std::cout << "     ROW/COLUMN ACCESS TEST" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    printMatrix(m1, "m1");
    std::cout << std::endl;
    
    auto row1 = m1.getRow(1);
    std::cout << "Row 1 of m1: [";
    for (size_t i = 0; i < 3; ++i) {
        std::cout << std::setw(8) << row1[i];
        if (i < 2) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    
    auto col2 = m1.getColumn(2);
    std::cout << "Column 2 of m1: [";
    for (size_t i = 0; i < 3; ++i) {
        std::cout << std::setw(8) << col2[i];
        if (i < 2) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl;
    
    // Test modifying a matrix using setRow and setColumn
    Matrix<double, 3, 3> m7 = Matrix<double, 3, 3>::identity();
    Vector<double, 3> newRow = {10.0, 20.0, 30.0};
    m7.setRow(0, newRow);
    
    Vector<double, 3> newCol = {100.0, 200.0, 300.0};
    m7.setColumn(2, newCol);
    
    printMatrix(m7, "Modified Identity (row 0 & col 2 changed)");
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "          PSEUDOINVERSE TEST" << std::endl;
    std::cout << "========================================" << std::endl;

    Matrix<double, 3, 2> m8 = {
        1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0
	};

	printMatrix(m8, "m8 (3x2)");
	auto m8_pinv = m8.pseudoInverse();
	printMatrix(m8_pinv, "Pseudo-inverse of m8");
	
	// Verify pseudo-inverse property: A * A^+ * A ≈ A
	auto m8_test = m8 * m8_pinv;
	auto m8_reconstructed = m8_test * m8;
	bool pinv_valid = true;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 2; j++) {
			if (std::abs(m8_reconstructed(i, j) - m8(i, j)) > 1e-10) {
				pinv_valid = false;
			}
		}
	}
	assert_true(pinv_valid, "Pseudo-inverse property A*A^+*A ≈ A");
	
	// Check that result is not NaN
	bool has_nan = false;
	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (std::isnan(m8_pinv(i, j))) {
				has_nan = true;
			}
		}
	}
	assert_true(!has_nan, "Pseudo-inverse contains no NaN values");

    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "         TEST SUMMARY" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Tests Passed: " << tests_passed << std::endl;
    std::cout << "Tests Failed: " << tests_failed << std::endl;
    std::cout << "Total Tests:  " << (tests_passed + tests_failed) << std::endl;
    
    if (tests_failed == 0) {
        std::cout << "\n✓ ALL TESTS PASSED!" << std::endl;
        return 0;
    } else {
        std::cout << "\n✗ SOME TESTS FAILED!" << std::endl;
        return 1;
    }
}
