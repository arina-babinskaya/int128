CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN = app

SRCS = \
    src/main.cpp \
	src/expression.cpp \
    src/int128.cpp \
    src/const.cpp \
    src/variable.cpp \
    src/negate.cpp \
    src/add.cpp \
    src/subtract.cpp \
    src/multiply.cpp \
    src/divide.cpp

OBJS = $(SRCS:src/%.cpp=$(OBJ_DIR)/%.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN)

rebuild: clean all
