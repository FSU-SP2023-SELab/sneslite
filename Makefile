# Compiler and flags
CXX := g++
CXXFLAGS := \
			-std=c++20 \
			-Wall \
			-Wextra \
			-Wfatal-errors \
			-pedantic \

# Directories
SRC_DIR		:= ./src
TEST_DIR	:= ./tests
BUILD_DIR	:= ./build

# Executable build location
EXECUTABLE	:= $(BUILD_DIR)/unit_test.o

# Source files
MAIN_SRC	:= $(SRC_DIR)/main.cpp
TEST_SRC	:= $(TEST_DIR)/main.cpp

# Append new sources here
OBJECTS		:= 	\
				$(SRC_DIR)/debug/Logger.cpp \
				$(SRC_DIR)/cartridge/Cartridge.cpp \
				$(SRC_DIR)/cpu/Cpu.cpp \
				$(SRC_DIR)/cpu/Bus.cpp \
				$(SRC_DIR)/apu/Apu.cpp \
				$(SRC_DIR)/ppu/Ppu.cpp \

.PHONY: all clean

all: $(MAIN_SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(MAIN_SRC) $(OBJECTS)

test: $(TEST_SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(TEST_SRC) $(OBJECTS)

clean:
	rm -rf $(BUILD_DIR)/