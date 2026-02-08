# VexRobotics

![Build and Test](https://github.com/NGminecraft/VexRobotics/workflows/Build%20and%20Test/badge.svg?branch=dev)

A C++ library for robotics applications with linear algebra utilities optimized for VEX robotics competitions.

## Features

### DataTypes Library
- **Vectors**: Compile-time sized vectors with owning and non-owning variants
  - Scalar and elementwise operations
  - Cross products
  - Strided access for matrix rows/columns
  
- **Matrices**: Compile-time sized matrices with comprehensive operations
  - Matrix multiplication
  - Transpose
  - Pseudo-inverse (Moore-Penrose) using Cholesky decomposition
  - Row/column access and modification

## Building

### Requirements
- C++11 compatible compiler (GCC/G++, MinGW, Clang)
- Make or MinGW32-Make

### Compile and Run Tests

**Linux/macOS:**
```bash
cd Testing/DataTypesTest
make
./test_datatypes
```

**Windows:**
```cmd
cd Testing\DataTypesTest
mingw32-make
test_datatypes.exe
```

## Continuous Integration

This project uses GitHub Actions for automated testing across multiple platforms:
- ? Linux (Ubuntu)
- ? Windows (MinGW)
- ? macOS

See [CI Documentation](.github/CI_README.md) for details.

## Project Structure

```
VexRobotics/
??? include/
?   ??? DataTypes/
?       ??? Vectors.h       # Vector implementation
?       ??? Matrix.h        # Matrix implementation
??? Testing/
?   ??? DataTypesTest/
?       ??? main.cpp        # Test suite
?       ??? Makefile        # Build configuration
??? .github/
?   ??? workflows/
?       ??? build-and-test.yml  # CI/CD pipeline
??? README.md
```

## Usage Examples

### Vectors
```cpp
#include "DataTypes/Vectors.h"

Vector<double, 3> v1 = {1.0, 2.0, 3.0};
Vector<double, 3> v2 = {4.0, 5.0, 6.0};

auto v3 = v1 * 2.0;           // Scalar multiplication
auto v4 = v1 * v2;            // Elementwise multiplication
auto v5 = v1.cross(v2);       // Cross product
double sum = v1.sum();        // Sum of elements
```

### Matrices
```cpp
#include "DataTypes/Matrix.h"

Matrix<double, 3, 3> m1 = {
    1.0, 2.0, 3.0,
    4.0, 5.0, 6.0,
    7.0, 8.0, 9.0
};

auto identity = Matrix<double, 3, 3>::identity();
auto transposed = m1.transpose();
auto result = m1 * identity;

// Pseudo-inverse for non-square matrices
Matrix<double, 3, 2> A = { /* ... */ };
auto A_pinv = A.pseudoInverse();  // Returns 2x3 matrix
```

## License

[Add your license information here]

## Contributing

Contributions are welcome! Please ensure all tests pass before submitting a pull request.

```bash
cd Testing/DataTypesTest
make
./test_datatypes
```

## Development Branch

Active development happens on the `dev` branch. Pull requests should target `dev`.
