# Compiler options
CC = g++
OPTS = -std=c++17 -Wall -Wextra # -Werror

# Output options
OUTOPTS = -o
OUTPUT_FOLDER = out
OUT = $(OUTPUT_FOLDER)/trivia
TEST_OUT = $(OUTPUT_FOLDER)/trivia_tests

# Source definitions
SOURCE_FILES = src/GameRunner.cpp src/Game.cpp
FILES = $(SOURCE_FILES)
TEST_FILES = Game.cpp 

INCLUDES = \
	-I $(realpath .)/include

OBJS = \
    $(SOURCE_FILES:.cpp=.o)

OBJECTS = $(subst src/,$(OUTPUT_FOLDER)/,$(OBJS))

.PHONY: .outputFolder build clean tests
.INTERMEDIATE: .outputFolder

all: prod 

prod: build run

tests: test runTest

.outputFolder:
	mkdir -p $(OUTPUT_FOLDER)
	@echo $(OBJECTS)

build: .outputFolder $(OBJECTS)
	$(CC) $(OBJECTS) $(OUTOPTS) $(OUT)

$(OUTPUT_FOLDER)/%.o: src/%.cpp 
	@echo "Compiling $^"
	$(CC) $(OPTS) $(INCLUDES) -c $^ -o $@

run: build
	./$(OUT)

test: .outputFolder
	$(CC) $(TEST_FILES) $(OPTS) $(OUTOPTS) $(TEST_OUT)

runTest: 
	./$(TEST_OUT)

clean: 
	rm -rf $(OUTPUT_FOLDER)/
