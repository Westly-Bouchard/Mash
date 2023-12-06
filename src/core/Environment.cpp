//
// Created by Westly Bouchard on 12/4/23.
//

#include <sstream>

#include "../../include/core/Environment.h"

#include "../../include/tool/Error.hpp"

using namespace std;

Value::Value() {
    currentType = ValueType::INT;
    asInt = 0;
}

Value::Value(const ValueType kind, const int initialValue) : currentType(kind) {
    asInt = initialValue;
}

Value::Value(const ValueType kind, const double initialValue) : currentType(kind) {
    asDouble = initialValue;
}

Value::Value(const ValueType kind, const bool initialValue) : currentType(kind) {
    asBool = initialValue;
}

Value::Value(const ValueType kind, const string& initialValue) : currentType(kind) {
    asString = initialValue;
}

Value::Value(Value& other) {
    this->currentType = other.getType();

    switch (this->currentType) {
        case ValueType::INT: {
            this->asInt = other.getInt();
        }

        case ValueType::DOUBLE: {
            this->asDouble = other.getDouble();
        }

        case ValueType::BOOL: {
            this->asBool = other.getBool();
        }

        case ValueType::STRING: {
            this->asString = other.getString();
        }
    }

    other.~Value();
}

Value::~Value() {
    switch (currentType) {
        case ValueType::INT:
        case ValueType::DOUBLE:
        case ValueType::BOOL:
            break;

        case ValueType::STRING:
            asString.~string();
    }
}

ValueType Value::getType() const {
    return this->currentType;
}


bool Value::isOfType(const ValueType kind) const {
    return this->currentType == kind;
}

bool Value::sameTypeAs(const Value& other) const {
    return this->isOfType(other.getType());
}

bool Value::isTruthy() const {
    switch (this->currentType) {
        case ValueType::INT: {
            return asInt != 0;
        }

        case ValueType::DOUBLE: {
            return asDouble != 0;
        }

        case ValueType::BOOL: {
            return asBool;
        }

        case ValueType::STRING: {
            return true;
        }
    }

    return true;
}

bool Value::isNumeric() const {
    return this->currentType == ValueType::INT || this->currentType == ValueType::DOUBLE;
}

bool Value::areSameType(const Value& one, const Value& two) {
    return one.sameTypeAs(two);
}

bool Value::areBoth(const ValueType kind, const Value& one, const Value& two) {
    return one.isOfType(kind) && two.isOfType(kind);
}

void Value::set(const int newValue) {
    this->currentType = ValueType::INT;

    asInt = newValue;
}

void Value::set(const double newValue) {
    this->currentType = ValueType::DOUBLE;

    asDouble = newValue;
}

void Value::set(const bool newValue) {
    this->currentType = ValueType::BOOL;

    asBool = newValue;
}

void Value::set(const string& newValue) {
    this->currentType = ValueType::STRING;

    asString = newValue;
}

int Value::getInt() const {
    if (this->currentType == ValueType::INT) {
        return asInt;
    }

    throw runtime_error("Attept to access value as int, when type not int");
}

double Value::getDouble()const {
    if (this->currentType == ValueType::DOUBLE) {
        return asDouble;
    }

    throw runtime_error("Attemt to access value as double, when type not double");
}

bool Value::getBool() const {
    if (this->currentType == ValueType::BOOL) {
        return asBool;
    }

    throw runtime_error("Attemtpt to access value as bool, when type not bool");
}

std::string Value::getString() const {
    if (this->currentType == ValueType::STRING) {
        return asString;
    }

    throw runtime_error("Attempt to access value as string, when value not string");
}

bool Value::operator==(const Value& other) const {
    if (this->isOfType(ValueType::STRING) && other.isOfType(ValueType::STRING)) {
        return getString() == other.getString();
    }

    if (this->isNumeric() && other.isNumeric()) {

    }
}



void Environment::define(const string& name, Value& value) {
    if (!values.contains(name)) {
        values[name] = make_unique<Value>(value);
        return;
    }

    stringstream ss;
    ss << "Error declaring variable: " << name << "Variable with same name already exists" << endl;
    throw mash::RuntimeError(ss.str());
}

std::unique_ptr<Value>& Environment::get(const Token& name) {
    if (values.contains(name.lexeme)) {
        return values.at(name.lexeme);
    }

    stringstream ss;
    ss << "Error accessing variable: " << name.lexeme << ", a variable with this name does not exist" << endl;
    throw mash::RuntimeError(ss.str());
}
