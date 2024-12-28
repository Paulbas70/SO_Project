# Compiler and Flags
CC := gcc
CFLAGS := -Wall -Wextra -I src -g

# Directories
SRC_DIR := src
TST_DIR := tst
OBJ_DIR := obj
OBJ_SRC_DIR := $(OBJ_DIR)/src
OBJ_TST_DIR := $(OBJ_DIR)/tst
BIN_DIR := bin

# Source files for the main executable
MAIN_SRC := $(SRC_DIR)/main.c
LIB_SRC := $(filter-out $(MAIN_SRC), $(wildcard $(SRC_DIR)/*.c))
LIB_OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_SRC_DIR)/%.o, $(LIB_SRC))
MAIN_OBJ := $(OBJ_SRC_DIR)/main.o
MAIN_EXE := $(BIN_DIR)/main

# Automatically detect all .c files in tst/ and extract their basenames
TEST_SOURCES := $(wildcard $(TST_DIR)/*.c)
TEST_NAMES := $(basename $(notdir $(TEST_SOURCES)))
TEST_EXECUTABLES := $(addprefix $(BIN_DIR)/, $(TEST_NAMES))
TEST_OBJECTS := $(patsubst $(TST_DIR)/%.c, $(OBJ_TST_DIR)/%.o, $(TEST_SOURCES))

# Default Target
all: $(MAIN_EXE)

# Building the Main Executable
$(MAIN_EXE): $(MAIN_OBJ) $(LIB_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule to build each test executable
$(BIN_DIR)/%: $(OBJ_TST_DIR)/%.o $(LIB_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile src/main.c into obj/src/main.o
$(OBJ_SRC_DIR)/main.o: $(MAIN_SRC) | $(OBJ_SRC_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile other src/*.c into obj/src/*.o
$(OBJ_SRC_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_SRC_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile tst/*.c into obj/tst/*.o
$(OBJ_TST_DIR)/%.o: $(TST_DIR)/%.c | $(OBJ_TST_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure all necessary directories exist
$(OBJ_DIR) $(OBJ_SRC_DIR) $(OBJ_TST_DIR) $(BIN_DIR):
	mkdir -p $@

# Tests Target
tests: $(TEST_EXECUTABLES)

# Clean Target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Prevent Object Files from Being Removed
.SECONDARY: $(LIB_OBJ) $(TEST_OBJECTS) $(MAIN_OBJ)

# Phony Targets
.PHONY: all tests clean