TARGET = mash

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm -f
endif

CXX = g++
CXXFLAGS = -Wall -g -std=c++17

all: makemash

makemash: setup link
	@echo "[INFO]: Mash Executable Built"

##--------------------------------------------------------------------------------------------------
DEST = build
OBJ_DEST = $(DEST)/objects

SRC_PATH = src
CORE_PATH = core
EXPR_PATH = expr
STMT_PATH = stmt
TOOL_PATH = tool
##--------------------------------------------------------------------------------------------------
CORE_SRC_PATH = $(SRC_PATH)/$(CORE_PATH)
CORE_OBJ_PATH = $(OBJ_DEST)/$(CORE_PATH)

CORE_SRC_FILES = main.cpp Parser.cpp Scanner.cpp Token.cpp TokenType.cpp

CORE_OBJECTS = $(CORE_SRC_FILES:%.cpp=$(CORE_OBJ_PATH)/%.o)

$(CORE_OBJ_PATH)/%.o: $(CORE_SRC_PATH)/%.cpp
	@echo "    Building $@"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
##--------------------------------------------------------------------------------------------------
EXPR_SRC_PATH = $(SRC_PATH)/$(EXPR_PATH)
EXPR_OBJ_PATH = $(OBJ_DEST)/$(EXPR_PATH)

EXPR_SRC_FILES = Binary.cpp Grouping.cpp Literal.cpp Unary.cpp Variable.cpp

EXPR_OBJECTS = $(EXPR_SRC_FILES:%.cpp=$(EXPR_OBJ_PATH)/%.o)

$(EXPR_OBJ_PATH)/%.o: $(EXPR_SRC_PATH)/%.cpp
	@echo "    Building $@"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
##--------------------------------------------------------------------------------------------------
STMT_SRC_PATH = $(SRC_PATH)/$(STMT_PATH)
STMT_OBJ_PATH = $(OBJ_DEST)/$(STMT_PATH)

STMT_SRC_FILES = Block.cpp Echo.cpp Exec.cpp Expression.cpp For.cpp If.cpp VarAssign.cpp \
				 VarDecl.cpp While.cpp

STMT_OBJECTS = $(STMT_SRC_FILES:%.cpp=$(STMT_OBJ_PATH)/%.o)

$(STMT_OBJ_PATH)/%.o: $(STMT_SRC_PATH)/%.cpp
	@echo "    Building $@"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
##--------------------------------------------------------------------------------------------------
TOOL_SRC_PATH = $(SRC_PATH)/$(TOOL_PATH)
TOOL_OBJ_PATH = $(OBJ_DEST)/$(TOOL_PATH)

TOOL_SRC_FILES = ASTWriter.cpp ArgParser.cpp

TOOL_OBJECTS = $(TOOL_SRC_FILES:%.cpp=$(TOOL_OBJ_PATH)/%.o)

$(TOOL_OBJ_PATH)/%.o: $(TOOL_SRC_PATH)/%.cpp
	@echo "    Building $@"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
##--------------------------------------------------------------------------------------------------

link: core expr stmt tool
	@echo "[INFO]: Linking Objects"
	@$(CXX) -o $(TARGET) $(CORE_OBJECTS) $(EXPR_OBJECTS) $(STMT_OBJECTS) $(TOOL_OBJECTS)

core: $(CORE_OBJECTS)
	@echo "[INFO]: Building Mash Core Objects"

expr: $(EXPR_OBJECTS)
	@echo "[INFO]: Building Mash Expr Objects"

stmt: $(STMT_OBJECTS)
	@echo "[INFO]: Building Mash Stmt Objects"

tool: $(TOOL_OBJECTS)
	@echo "[INFO]: Building Mash Tool Objects"

setup:
	@mkdir -p $(DEST)
	@mkdir -p $(OBJ_DEST)
	@mkdir -p $(OBJ_DEST)/$(CORE_PATH)
	@mkdir -p $(OBJ_DEST)/$(EXPR_PATH)
	@mkdir -p $(OBJ_DEST)/$(STMT_PATH)
	@mkdir -p $(OBJ_DEST)/$(TOOL_PATH)

clean:
	@rm -fr $(DEST)

.PHONY: clean all setup core expr stmt tool makemash