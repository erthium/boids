CC := g++
CFLAGS := -Wall -std=c++11 -I/usr/include/SDL2 -Iinclude
TEST_CFLAGS := -Wall -std=c++11 -I/usr/include/SDL2 -Isrc/ -Iinclude
LDFLAGS := -lSDL2 -lSDL2_image

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
TEST_DIR := test
STABLE_DIR := stable

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))
EXE_NAME := boids.follow
EXECUTABLE := $(BIN_DIR)/$(EXE_NAME)
STABLE_EXE := $(STABLE_DIR)/$(EXE_NAME)

TEST_SRC := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRC))
TEST_EXECUTABLE := $(BIN_DIR)/boids.where

.PHONY: all clean run test ship stable unplug

all: clean $(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(TEST_CFLAGS) -c $< -o $@

$(TEST_EXECUTABLE): $(TEST_OBJ) $(filter-out $(BUILD_DIR)/main.o, $(OBJ))
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(BUILD_DIR)/*.o $(BIN_DIR)/*

run: $(EXECUTABLE)
	./$(EXECUTABLE)

ship: $(EXECUTABLE)
	@mkdir -p $(STABLE_DIR)
	cp $(EXECUTABLE) $(STABLE_DIR)/

stable: $(STABLE_EXE)
	./$(STABLE_EXE)

unplug:
	rm -f $(STABLE_DIR)/*
