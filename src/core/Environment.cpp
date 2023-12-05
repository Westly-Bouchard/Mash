//
// Created by Westly Bouchard on 12/4/23.
//

#include <sstream>

#include "../../include/core/Environment.h"

#include "../../include/tool/Error.hpp"

using namespace std;

void Environment::define(const string& name, const VALUE_TYPE& value) {
    if (!values.contains(name)) {
        values.emplace(name, value);
        return;
    }

    stringstream ss;
    ss << "Error declaring variable: " << name << "Variable with same name already exists" << endl;
    throw mash::RuntimeError(ss.str());
}

VALUE_TYPE Environment::get(const Token& name) const {
    if (values.contains(name.lexeme)) {
        return values.at(name.lexeme);
    }

    stringstream ss;
    ss << "Error accessing variable: " << name.lexeme << ", a variable with this name does not exist" << endl;
    throw mash::RuntimeError(ss.str());
}
