TARGET = mash

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = rmdir /s /q
	CREATE = -mkdir
	CXX = g++.exe
	SEP = \\
else
	DEL = rm -fr
	CREATE = mkdir -p
	CXX = g++
	SEP = /
endif

CXXFLAGS = -Wall -g -std=c++20

all: makemash

makemash: setup link
	@echo "[INFO]: Mash Executable Built"

##--------------------------------------------------------------------------------------------------
DEST = build
OBJ_DEST = $(DEST)$(SEP)objects

SRC_PATH = src
CORE_PATH = core
EXPR_PATH = expr
STMT_PATH = stmt
TOOL_PATH = tool
##--------------------------------------------------------------------------------------------------
CORE_SRC_PATH = $(SRC_PATH)$(SEP)$(CORE_PATH)
CORE_OBJ_PATH = $(OBJ_DEST)$(SEP)$(CORE_PATH)

CORE_SRC_FILES = main.cpp Parser.cpp Scanner.cpp Token.cpp TokenType.cpp Interpreter.cpp Environment.cpp

CORE_OBJECTS = $(CORE_SRC_FILES:%.cpp=$(CORE_OBJ_PATH)$(SEP)%.o)

$(CORE_OBJ_PATH)$(SEP)%.o: $(CORE_SRC_PATH)$(SEP)%.cpp
	@echo "    Building $@"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
##--------------------------------------------------------------------------------------------------
EXPR_SRC_PATH = $(SRC_PATH)$(SEP)$(EXPR_PATH)
EXPR_OBJ_PATH = $(OBJ_DEST)$(SEP)$(EXPR_PATH)

EXPR_SRC_FILES = Binary.cpp Grouping.cpp Literal.cpp Unary.cpp Variable.cpp

EXPR_OBJECTS = $(EXPR_SRC_FILES:%.cpp=$(EXPR_OBJ_PATH)$(SEP)%.o)

$(EXPR_OBJ_PATH)$(SEP)%.o: $(EXPR_SRC_PATH)$(SEP)%.cpp
	@echo "    Building $@"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
##--------------------------------------------------------------------------------------------------
STMT_SRC_PATH = $(SRC_PATH)$(SEP)$(STMT_PATH)
STMT_OBJ_PATH = $(OBJ_DEST)$(SEP)$(STMT_PATH)

STMT_SRC_FILES = Block.cpp Echo.cpp Exec.cpp Expression.cpp For.cpp If.cpp VarAssign.cpp \
				 VarDecl.cpp While.cpp

STMT_OBJECTS = $(STMT_SRC_FILES:%.cpp=$(STMT_OBJ_PATH)$(SEP)%.o)

$(STMT_OBJ_PATH)$(SEP)%.o: $(STMT_SRC_PATH)$(SEP)%.cpp
	@echo "    Building $@"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
##--------------------------------------------------------------------------------------------------
TOOL_SRC_PATH = $(SRC_PATH)$(SEP)$(TOOL_PATH)
TOOL_OBJ_PATH = $(OBJ_DEST)$(SEP)$(TOOL_PATH)

TOOL_SRC_FILES = ASTWriter.cpp ArgParser.cpp

TOOL_OBJECTS = $(TOOL_SRC_FILES:%.cpp=$(TOOL_OBJ_PATH)$(SEP)%.o)

$(TOOL_OBJ_PATH)$(SEP)%.o: $(TOOL_SRC_PATH)$(SEP)%.cpp
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
	@$(CREATE) $(DEST)
	@$(CREATE) $(OBJ_DEST)
	@$(CREATE) $(OBJ_DEST)$(SEP)$(CORE_PATH)
	@$(CREATE) $(OBJ_DEST)$(SEP)$(EXPR_PATH)
	@$(CREATE) $(OBJ_DEST)$(SEP)$(STMT_PATH)
	@$(CREATE) $(OBJ_DEST)$(SEP)$(TOOL_PATH)

clean:
	@$(DEL) $(DEST)

.PHONY: clean all setup core expr stmt tool makemash