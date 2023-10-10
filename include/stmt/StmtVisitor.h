#ifndef STMT_VISITOR_H
#define STMT_VISITOR_H

class Expression;
class Echo; 
class Exec;
class VarDecl;
class VarAssign;
class If;
class For;
class While;
class For;
class Block;

template <typename R>
class StmtVisitor {
    public:
        virtual R visitExpressionStmt(const Expression *expressionStmt) = 0;
        virtual R visitEchoStmt(const Echo *echoStmt) = 0;
        virtual R visitExecStmt(const Exec *execStmt) = 0;
        virtual R visitVarDeclStmt(const VarDecl *varDeclStmt) = 0;
        virtual R visitVarAssignStmt(const VarAssign *varAssignStmt) = 0;
        virtual R visitIfStmt(const If *ifStmt) = 0;
        virtual R visitWhileStmt(const While *whileStmt) = 0;
        virtual R visitForStmt(const For *forStmt) = 0; 
        virtual R visitBlockStmt(const Block *blockStmt) = 0;
};

#endif