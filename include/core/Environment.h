//
// Created by Westly Bouchard on 12/4/23.
//

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include <variant>

#include "Token.h"

#define VALUE_TYPE std::variant<int, double, bool, std::string>

class Environment {
public:
    Environment() = default;

    void define(const std::string& name, const VALUE_TYPE& value);

    VALUE_TYPE get(const Token& name) const;

private:
    std::unordered_map<std::string, VALUE_TYPE> values;
};



#endif //ENVIRONMENT_H
