# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++20

# Directories
SRC_DIR := ../src
BUILD_DIR := build

# Executable build location
EXECUTABLE := $(BUILD_DIR)/unit_test.o

# Source files
MAIN_SRC := ./main.cpp
LOGGER_SRC := $(SRC_DIR)/debug/logger.cpp
CARTRIDGE_SRC := $(SRC_DIR)/cartridge/cartridge.cpp

# Append new sources here
OBJECTS := $(MAIN_SRC) $(LOGGER_SRC) $(CARTRIDGE_SRC) 

.PHONY: all clean

all: $(MAIN_SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

clean:
	rm -f $(BUILD_DIR)/