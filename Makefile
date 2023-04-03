# Compiler and flags
CXX := g++
CXXFLAGS := \
			-std=c++20 \
			-Wall \
			-Wextra \
			-Wfatal-errors \
			-pedantic \

SFMLFLAGS := \
			-lsfml-graphics \
			-lsfml-system \
			-lsfml-window

# Directories
SRC_DIR		:= ./src
TEST_DIR	:= ./tests
BUILD_DIR	:= ./build

# Executable build location
EXECUTABLE	:= $(BUILD_DIR)/unit_test.o

# Object build location
OBJECT		:= $(BUILD_DIR)/main.o

MAIN_EXEC	:= $(BUILD_DIR)/main.x

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

wrapper: $(MAIN_SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(MAIN_SRC) -o $(MAIN_EXEC) $(SFMLFLAGS)

clean:
	rm -rf $(BUILD_DIR)/