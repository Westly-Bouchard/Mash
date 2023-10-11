#ifndef BLOCK_H
#define BLOCK_H

#include <memory>
#include <vector>

#include "Stmt.h"

class Block : public Stmt {
    private:
        std::vector<std::unique_ptr<Stmt>> statements;

    public:
        Block(std::vector<std::unique_ptr<Stmt>> statements);

        std::any accept(StmtVisitor<std::any>& visitor) const override;
};

#endif