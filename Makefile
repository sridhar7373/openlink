CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

TARGET = $(BIN_DIR)/identity_test.exe

SRC = $(wildcard src/*.cpp)
TEST = $(wildcard tests/*.cpp)

OBJECTS = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
TEST_OBJECTS = $(patsubst tests/%.cpp,$(OBJ_DIR)/%.o,$(TEST))

all: $(TARGET)

$(TARGET): $(OBJECTS) $(TEST_OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) $(TEST_OBJECTS) -lsodium -o $(TARGET)

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: tests/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)