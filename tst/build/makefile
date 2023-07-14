# Include common settings
include ../../build/config.mk

OUTPUT_FOLDER = out
LIB_UNDER_TEST = $(OUTPUT_FOLDER)/libUT_trivia.a
PROGRAM = $(OUTPUT_FOLDER)/trivia_tests

INCLUDES = \
    -I $(realpath ../..)/include \
    -I/opt/homebrew/include

SRC_DIR = \
	$(realpath ../..)/src

TST_DIR = \
	$(realpath ..)/src

vpath %.cpp $(SRC_DIR)
vpath %.cpp $(TST_DIR)

LD_LIBRARIES += \
    -L/opt/homebrew/lib/ \
    -lgmock -lgtest

SRC_FILES = \
	$(wildcard $(SRC_DIR)/*.cpp)

TST_FILES = \
	$(wildcard $(TST_DIR)/*.cpp)

TST_OBJS = \
    $(subst $(TST_DIR)/,$(OUTPUT_FOLDER)/,$(TST_FILES:.cpp=.o))

SRC_OBJS = \
    $(subst $(SRC_DIR)/,$(OUTPUT_FOLDER)/,$(SRC_FILES:.cpp=.o))

.PHONY: .outputFolder clean runTest
.INTERMEDIATE: .outputFolder

all: runTest

.outputFolder:
	@mkdir -p $(OUTPUT_FOLDER)

$(PROGRAM): .outputFolder $(TST_OBJS) $(LIB_UNDER_TEST)
	$(LD) $(TST_OBJS) $(LD_LIBRARIES) -o $(PROGRAM)

$(LIB_UNDER_TEST): $(SRC_OBJS)
	$(AR) $(ARFLAGS) $(LIB_UNDER_TEST) $^

runTest: $(PROGRAM)
	./$(PROGRAM)

$(OUTPUT_FOLDER)/%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $^ -o $@

clean:
	@rm -rf $(OUTPUT_FOLDER)/
