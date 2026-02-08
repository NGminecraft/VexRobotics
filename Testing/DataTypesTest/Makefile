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

# Detect OS
ifeq ($(OS),Windows_NT)
    TARGET = test_datatypes.exe
    RM = cmd /C del /Q /F
    RMDIR = cmd /C rmdir /S /Q
    MKDIR = cmd /C mkdir
else
    TARGET = test_datatypes
    RM = rm -f
    RMDIR = rm -rf
    MKDIR = mkdir -p
endif

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts (cross-platform)
clean:
ifeq ($(OS),Windows_NT)
	-$(RM) $(OBJECTS) $(TARGET) 2>nul || exit 0
else
	-$(RM) $(OBJECTS) $(TARGET)
endif
	@echo Clean complete

# Run the test
run: $(TARGET)
ifeq ($(OS),Windows_NT)
	.\$(TARGET)
else
	./$(TARGET)
endif

.PHONY: all clean run
