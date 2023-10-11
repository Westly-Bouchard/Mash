#ifndef STMT_H
#define STMT_H

#include <any>

#include "StmtVisitor.h"

class Stmt {
    public:
        virtual ~Stmt() = default;
        virtual std::any accept(StmtVisitor<std::any>& visitor) const = 0;
};

#endif