# Include common settings
include config.mk

# Output options
OUTPUT_FOLDER = out
PROGRAM = $(OUTPUT_FOLDER)/trivia

INCLUDES = \
    -I $(realpath ..)/include

SRC_DIR = \
	$(realpath ..)/src

vpath %.cpp $(SRC_DIR)

# Source definitions
SOURCE_FILES = \
	$(wildcard $(SRC_DIR)/*.cpp)

OBJS = \
    $(subst $(SRC_DIR)/,$(OUTPUT_FOLDER)/,$(SOURCE_FILES:.cpp=.o))

.PHONY: .outputFolder build clean tests
.INTERMEDIATE: .outputFolder

all: build run

.outputFolder:
	@mkdir -p $(OUTPUT_FOLDER)

build: .outputFolder $(OBJS)
	$(LD) $(LD_FLAGS) $(LD_LIBRARIES) $(OBJS) -o $(PROGRAM)

run: build
	./$(PROGRAM)

tests:
	$(MAKE) -C ../tst/build COVERAGE=1
	$(RM) -rf coverage && mkdir -p coverage
	gcovr --exclude '.*/tst/.*' --html-details coverage/index.html --print-summary --root ..

$(OUTPUT_FOLDER)/%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) $^ -o $@

clean:
	@rm -rf $(OUTPUT_FOLDER)/
	$(MAKE) -C ../tst/build clean
