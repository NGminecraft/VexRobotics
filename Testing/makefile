.PHONY: all clean

# Folder with mock headers
MOCK_INC = ./Includes

# Project headers
PROJECT_INC = ../include

# Compiler (force GCC 11 if installed)
CXX = clang
CC  = clang

CFLAGS_V7 = -march=armv7-a -mfpu=neon -mfloat-abi=softfp
# Standard C++ version for CI/testing
CXX_FLAGS = -std=gnu++2a -O2 -Wall -Werror

# Include order:
# 1. Mock headers (stubs)
# 2. System headers (auto-found by compiler)
# 3. Project headers
INC_FLAGS = -I$(MOCK_INC) -I$(PROJECT_INC)

# Source files
SRC = $(wildcard ../src/*.cpp ../src/*/*.cpp)

# Output folder
BUILD = ../build
OBJ = $(patsubst ../src/%.cpp,$(BUILD)/%.o,$(SRC))
BIN = $(BUILD)/test.bin

# Default target
all: $(BIN)

# Link
$(BIN): $(OBJ)
	@mkdir -p $(BUILD)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $@

# Compile
$(BUILD)/%.o: ../src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)
