#include <iostream>
#include <iomanip>
#include "../../include/DataTypes/Vectors.h"
#include "../../include/DataTypes/Matrix.h"

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
    
    // Test elementwise multiplication
    auto v4 = v1 * v2;
    printVector(v4, "v1 * v2 (elementwise)");
    
    // Test cross product
    auto v5 = v1.cross(v2);
    printVector(v5, "v1 x v2 (cross product)");
    
    // Test sum
    std::cout << "Sum of v1: " << v1.sum() << std::endl;
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

    std::cout << "========================================" << std::endl;
    std::cout << "         ALL TESTS COMPLETE" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}
