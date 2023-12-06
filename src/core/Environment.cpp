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

Value::Value(ValueType kind) : currentType(kind) {
    switch (currentType) {
        case ValueType::INT: asInt = 0;
        case ValueType::DOUBLE: asDouble = 0.0;
        case ValueType::BOOL: asBool = false;
        case ValueType::STRING: asString = "";
    }
}

Value::Value(const int initialValue) : currentType(ValueType::INT) {
    asInt = initialValue;
}

Value::Value(const double initialValue) : currentType(ValueType::DOUBLE) {
    asDouble = initialValue;
}

Value::Value(const bool initialValue) : currentType(ValueType::BOOL) {
    asBool = initialValue;
}

Value::Value(const string& initialValue) : currentType(ValueType::STRING) {
    asString = initialValue;
}

Value::Value(Value& other) {
    this->currentType = other.getType();

    switch (this->currentType) {
        case ValueType::INT: {
            this->asInt = other.getInt();
            break;
        }

        case ValueType::DOUBLE: {
            this->asDouble = other.getDouble();
            break;
        }

        case ValueType::BOOL: {
            this->asBool = other.getBool();
            break;
        }

        case ValueType::STRING: {
            this->asString = other.getString();
            break;
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
    return currentType == kind;
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

double Value::getDouble() const {
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
    // If they're both strings, we can compare them
    if (this->isOfType(ValueType::STRING) && other.isOfType(ValueType::STRING)) {
        return getString() == other.getString();
    }

    // If only one of them is a stirng, then we can't compare them, this is a runtime error
    if (this->isOfType(ValueType::STRING) || other.isOfType(ValueType::STRING)) {
        throw mash::RuntimeError("Error, cannot compare string with non string type");
    }

    // If they are both numeric, then we can compare them
    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;
        if (this->currentType == ValueType::DOUBLE) {
            thisValue = asDouble;
        } else {
            thisValue = asInt;
        }

        if (other.getType() == ValueType::DOUBLE) {
            otherValue = other.getDouble();
        } else {
            otherValue = other.getInt();
        }

        return thisValue == otherValue;
    }

    // If only one is numeric, then we can't perform the comparison
    if (this->isNumeric() || other.isNumeric()) {
        throw mash::RuntimeError("Error, cannot compare numeric type with non-numeric type");
    }

    if (this->isOfType(ValueType::BOOL) && other.isOfType(ValueType::BOOL)) {
        return asBool == other.getBool();
    }

    throw mash::RuntimeError("Error, cannot compare types");

}

bool Value::operator!=(const Value& other) const {
    return !(*this == other);
}

bool Value::operator>(const Value& other) const {
    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;

        if (this->currentType == ValueType::DOUBLE) {
            thisValue = asDouble;
        } else {
            thisValue = asInt;
        }

        if (other.getType() == ValueType::DOUBLE) {
            otherValue = other.getDouble();
        } else {
            otherValue = other.getInt();
        }

        return thisValue > otherValue;
    }

    throw mash::RuntimeError("Error, both types must be numeric to perform comparison");
}

bool Value::operator<(const Value& other) const {
    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;

        if (this->currentType == ValueType::DOUBLE) {
            thisValue = asDouble;
        } else {
            thisValue = asInt;
        }

        if (other.getType() == ValueType::DOUBLE) {
            otherValue = other.getDouble();
        } else {
            otherValue = other.getInt();
        }

        return thisValue < otherValue;
    }

    throw mash::RuntimeError("Error, both types must be numeric to perform comparison");
}

bool Value::operator>=(const Value& other) const {
    return  *this > other || *this == other;
}

bool Value::operator<=(const Value&other) const {
    return *this < other || *this == other;
}

Value Value::operator*(const Value& other) const {
    if (areBoth(ValueType::INT, *this, other)) {
        return {asInt * other.getInt()};
    }

    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;

        if (this->currentType == ValueType::DOUBLE) {
            thisValue = asDouble;
        } else {
            thisValue = asInt;
        }

        if (other.getType() == ValueType::DOUBLE) {
            otherValue = other.getDouble();
        } else {
            otherValue = other.getInt();
        }

        return {thisValue * otherValue};
    }

    throw mash::RuntimeError("Error, cannot multiply types that are not both numeric");
}

Value& Value::operator=(const Value& other) {
    this->currentType = other.getType();

    switch (currentType) {
        case ValueType::INT:
            asInt = other.getInt();
            break;

        case ValueType::DOUBLE:
            asDouble = other.getDouble();
            break;

        case ValueType::BOOL:
            asBool = other.getBool();
            break;

        case ValueType::STRING:
            asString = other.getString();
            break;
    }

    return *this;
}


Value Value::operator/(const Value& other) const {
    if (areBoth(ValueType::INT, *this, other)) {
        return {asInt / other.getInt()};
    }

    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;

        if (this->currentType == ValueType::DOUBLE) {
            thisValue = asDouble;
        } else {
            thisValue = asInt;
        }

        if (other.getType() == ValueType::DOUBLE) {
            otherValue = other.getDouble();
        } else {
            otherValue = other.getInt();
        }

        return {thisValue / otherValue};
    }

    throw mash::RuntimeError("Error, cannot divide types that are not both numeric");
}

Value Value::operator-(const Value&other) const {
    if (areBoth(ValueType::INT, *this, other)) {
        return {asInt - other.getInt()};
    }

    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;

        if (this->currentType == ValueType::DOUBLE) {
            thisValue = asDouble;
        } else {
            thisValue = asInt;
        }

        if (other.getType() == ValueType::DOUBLE) {
            otherValue = other.getDouble();
        } else {
            otherValue = other.getInt();
        }

        return {thisValue - otherValue};
    }

    throw mash::RuntimeError("Error, cannot subtract types that are not both numeric");
}

Value Value::operator+(const Value& other) const {
    if (areBoth(ValueType::INT, *this, other)) {
        return {asInt + other.getInt()};
    }

    if (areBoth(ValueType::STRING, *this, other)) {
        return {asString + other.getString()};
    }

    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;

        if (this->currentType == ValueType::DOUBLE) {
            thisValue = asDouble;
        } else {
            thisValue = asInt;
        }

        if (other.getType() == ValueType::DOUBLE) {
            otherValue = other.getDouble();
        } else {
            otherValue = other.getInt();
        }

        return {thisValue + otherValue};
    }

    throw mash::RuntimeError("Error, cannot add the provided types");
}

std::ostream& operator<<(std::ostream& os, const Value& val) {
    switch (val.getType()) {
        case ValueType::INT: {
            os << val.getInt();
            break;
        }

        case ValueType::DOUBLE: {
            os << val.getDouble();
            break;
        }

        case ValueType::BOOL: {
            os << val.getBool();
            break;
        }

        case ValueType::STRING: {
            os << val.getString();
            break;
        }
    }
    return os;
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

void Environment::assign(const Token& name, Value& value) {
    if (values.contains(name.lexeme)) {
        values[name.lexeme] = make_unique<Value>(value);
    }

    stringstream ss;
    ss << "Error assigning variable: " << name.lexeme << " is not defined in the current scope" << endl;
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
