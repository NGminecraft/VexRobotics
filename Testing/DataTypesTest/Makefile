# Compiler settings - Use standard g++ from MinGW
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I../../include
LDFLAGS = -static-libgcc -static-libstdc++

# Directories
SRC_DIR = .
INCLUDE_DIR = ../../include
DATATYPES_DIR = $(INCLUDE_DIR)/DataTypes

# Source files
SOURCES = main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Output executable  
TARGET = test_datatypes.exe

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts (Windows)
clean:
	-del /Q $(OBJECTS) $(TARGET) 2>nul
	@echo Clean complete

# Run the test
run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean run
