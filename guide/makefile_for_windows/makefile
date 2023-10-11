# Makefile for Windows
# Note: Please replace src, include, 

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++17

# SFML directories
SFML_DIR = /path/to/SFML

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

# Include and library directories for SFML
INCLUDES = -I$(SFML_DIR)/include
LDFLAGS = -L$(SFML_DIR)/lib

# Source directory
SRC_DIR = src

# Header directory
INC_DIR = include

# Build directory
BUILD_DIR = build

# Target executable name
TARGET = chess

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Header files
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(SFML_LIBS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<