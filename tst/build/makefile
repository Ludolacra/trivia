# Include common settings
include ../../build/config.mk

CXX_FLAGS += \
	-g \
	$(if $(filter 1, $(SANITIZERS)),-fsanitize=address -fsanitize=undefined,)\
	$(if $(filter 1, $(COVERAGE)),--coverage,)

OUTPUT_FOLDER = out
LIB_UNDER_TEST = $(OUTPUT_FOLDER)/libUT_trivia.a
PROGRAM = $(OUTPUT_FOLDER)/trivia_tests

INCLUDES = \
    -I $(realpath ../..)/include \
    -I $(realpath ..)/include \
    -I /opt/homebrew/include \
    -I /usr/include

SRC_DIR = \
	$(realpath ../..)/src

TST_DIR = \
	$(realpath ..)/src

vpath %.cpp $(SRC_DIR)
vpath %.cpp $(TST_DIR)

LD_LIBRARIES += \
    -L/opt/homebrew/lib/ \
    -L/usr/lib/x86_64-linux-gnu \
    -lgmock -lgtest \
    -L$(OUTPUT_FOLDER) -lUT_trivia

LD_FLAGS += \
	$(if $(filter 1, $(SANITIZERS)),-fsanitize=address -fsanitize=undefined,)\
	$(if $(filter 1, $(COVERAGE)),--coverage,)

TST_FILES = \
	$(wildcard $(TST_DIR)/*.cpp)

TST_OBJS = \
    $(subst $(TST_DIR)/,$(OUTPUT_FOLDER)/,$(TST_FILES:.cpp=.o))

SRC_FILES = \
	$(wildcard $(SRC_DIR)/*.cpp)

SRC_OBJS = \
    $(subst $(SRC_DIR)/,$(OUTPUT_FOLDER)/,$(SRC_FILES:.cpp=.o))

.PHONY: .outputFolder clean runTest
.INTERMEDIATE: .outputFolder

all: runTest

.outputFolder:
	@mkdir -p $(OUTPUT_FOLDER)

$(PROGRAM): .outputFolder $(TST_OBJS) $(LIB_UNDER_TEST)
	$(LD) $(TST_OBJS) $(LD_FLAGS) $(LD_LIBRARIES) -o $(PROGRAM)

$(LIB_UNDER_TEST): $(SRC_OBJS)
	$(AR) $(ARFLAGS) $(LIB_UNDER_TEST) $^

runTest: $(PROGRAM)
	@rm -rf $(OUTPUT_FOLDER)/*.gcda
	ASAN_OPTIONS=detect_leaks=1 ./$(PROGRAM)

$(OUTPUT_FOLDER)/%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) $^ -o $@

clean:
	@rm -rf $(OUTPUT_FOLDER)/
