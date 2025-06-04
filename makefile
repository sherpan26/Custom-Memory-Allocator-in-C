
#compiles everything even memtest.c
CC = gcc
CFLAGS = -Wall -g
INCLUDES = -Iinclude

# Source and Object files
SRC_DIR = src
TESTS_DIR = tests
OBJ_DIR = obj
BIN_DIR = .

# Main program source and object files
MAIN_SRCS = $(SRC_DIR)/memgrind.c $(SRC_DIR)/memtest.c
MAIN_OBJS = $(MAIN_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Library source and object files
LIB_SRCS = $(SRC_DIR)/mymalloc.c
LIB_OBJS = $(LIB_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Test programs source and object files
TEST_SRCS = $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJS = $(TEST_SRCS:$(TESTS_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_BINS = $(TEST_SRCS:$(TESTS_DIR)/%.c=$(BIN_DIR)/%)

# Phony targets
.PHONY: all directories clean run tests

# Default target
all: directories memgrind memtest tests

# Create directories
directories: | $(OBJ_DIR)

$(OBJ_DIR):
    mkdir -p $(OBJ_DIR)

# Compile main program object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
    $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link the main program
memgrind: $(OBJ_DIR)/memgrind.o $(LIB_OBJS)
    $(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

# Link the memtest program
memtest: $(OBJ_DIR)/memtest.o $(LIB_OBJS)
    $(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

# Compile and link test programs
tests: $(TEST_BINS)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(LIB_OBJS)
    $(CC) $(CFLAGS) -o $@ $^

# Pattern rule for compiling test program object files
$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.c
    $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up the build
clean:
    rm -rf $(OBJ_DIR) $(BIN_DIR)/memgrind $(BIN_DIR)/memtest $(TEST_BINS)

# Compile and run 'memgrind'
run: memgrind
    ./$(BIN_DIR)/memgrind



    


    # Define the compiler
CC = gcc

# Define compiler flags
CFLAGS = -Wall -g

# Define the include directory
INCLUDES = -Iinclude

# Define source and object directories
SRC_DIR = src
OBJ_DIR = obj
TESTS_DIR = tests
BIN_DIR = bin

# Define source and object files for the main program and tests
MAIN_SRCS = $(wildcard $(SRC_DIR)/*.c)
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
TEST_SRCS = $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJS = $(patsubst $(TESTS_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))
TEST_BINS = $(patsubst $(TESTS_DIR)/%.c,$(BIN_DIR)/%,$(TEST_SRCS))

# Phony targets
.PHONY: all clean directories tests

# Default target
all: directories $(BIN_DIR)/memgrind $(TEST_BINS)

# Create directories
directories: | $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR):
    mkdir -p $(OBJ_DIR)

$(BIN_DIR):
    mkdir -p $(BIN_DIR)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
    $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link the main program
$(BIN_DIR)/memgrind: $(OBJ_DIR)/memgrind.o $(OBJ_DIR)/mymalloc.o
    $(CC) $(CFLAGS) -o $@ $^

# Link the test programs
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJ_DIR)/mymalloc.o
    $(CC) $(CFLAGS) -o $@ $^

# Compile test source files to object files
$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.c
    $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up the build
clean:
    rm -rf $(OBJ_DIR) $(BIN_DIR)

# Include dependencies
-include $(MAIN_OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)
