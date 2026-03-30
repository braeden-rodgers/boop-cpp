# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -g -Iinclude

# Directories
SRC_DIR = src
APP_DIR = app
BUILD_DIR = build

# Object files
SRC = $(SRC_DIR)/game.cc $(SRC_DIR)/boop.cc $(APP_DIR)/main.cc
OBJS = $(BUILD_DIR)/game.o $(BUILD_DIR)/boop.o $(BUILD_DIR)/main.o

# Target executable name
TARGET = $(BUILD_DIR)/boop

# Default rule
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile source files into object files within build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(APP_DIR)/main.cc
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

run: all 
	./$(TARGET)
