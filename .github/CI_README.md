# VexRobotics CI/CD

This repository uses GitHub Actions for continuous integration and testing.

## Build Status

![Build and Test](https://github.com/NGminecraft/VexRobotics/workflows/Build%20and%20Test/badge.svg)

## Workflows

### Build and Test
- **Trigger**: Push or pull request to `dev`, `main`, or `master` branches
- **Platforms**: Linux (Ubuntu), Windows, and macOS
- **Actions**:
  1. Checkout code
  2. Install build dependencies (g++, MinGW)
  3. Build the DataTypes test suite
  4. Run automated tests
  5. Upload test artifacts

## Local Testing

### Linux/macOS
```bash
cd Testing/DataTypesTest
make clean
make
./test_datatypes
```

### Windows (MinGW)
```cmd
cd Testing\DataTypesTest
mingw32-make clean
mingw32-make
test_datatypes.exe
```

### Windows (with Make)
```cmd
cd Testing\DataTypesTest
make clean
make
test_datatypes.exe
```

## Test Structure

The test suite includes:
- ? Vector operations (scalar multiplication, elementwise multiplication, cross product)
- ? Matrix operations (transpose, multiplication)
- ? Matrix-vector operations
- ? Row/column access
- ? Pseudo-inverse computation

## Exit Codes

- `0`: All tests passed ?
- `1`: One or more tests failed ?

## Adding New Tests

To add a new test:

1. Add your test code in `Testing/DataTypesTest/main.cpp`
2. Use `assert_equals()` or `assert_true()` for validation
3. Run locally to verify
4. Push to your branch - CI will automatically run

Example:
```cpp
// Test some feature
auto result = myFunction(input);
assert_equals(result, expectedValue, "MyFunction test");
```

## Build Configuration

- **C++ Standard**: C++11
- **Compiler**: GCC/G++ (MinGW on Windows)
- **Flags**: `-std=c++11 -Wall -Wextra`
- **Include Path**: `../../include`

## Artifacts

Test results and logs are uploaded as artifacts for each platform and can be downloaded from the GitHub Actions run page.
