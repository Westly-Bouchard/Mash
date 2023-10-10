#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "Stmt.h"

class Block : public Stmt {
    private:
        std::vector<Stmt*> statements;

    public:
        Block(std::vector<Stmt*> statements);

        std::any accept(StmtVisitor<std::any> *visitor) const override;
};

#endif