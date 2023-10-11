TARGET = mash

CORE_SRC = src/main.cpp src/Scanner.cpp src/Token.cpp src/TokenType.cpp src/Parser.cpp
EXPR_SRC = src/expr/Binary.cpp src/expr/Grouping.cpp src/expr/Literal.cpp src/expr/Unary.cpp
STMT_SRC = src/stmt/Block.cpp src/stmt/Echo.cpp src/stmt/Exec.cpp src/stmt/Expression.cpp src/stmt/For.cpp src/stmt/If.cpp src/stmt/VarAssign.cpp src/stmt/VarDecl.cpp src/stmt/While.cpp

SRC_FILES = $(CORE_SRC) $(EXPR_SRC) $(STMT_SRC)

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CXXVERSION) -g -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)

.PHONY: all clean depend
