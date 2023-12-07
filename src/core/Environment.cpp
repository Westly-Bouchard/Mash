//
// Created by Westly Bouchard on 12/4/23.
//

#include <sstream>

#include "../../include/core/Environment.h"

#include "../../include/tool/Error.hpp"

using namespace std;

Value::Value() {
    currentType = ValueType::INT;
    data = 0;
}

Value::Value(ValueType kind) : currentType(kind) {
    switch (currentType) {
        case ValueType::INT: {
            data = 0;
            break;
        }
        case ValueType::DOUBLE: {
            data = 0.0;
            break;
        }
        case ValueType::BOOL: {
            data = false;
            break;
        }
        case ValueType::STRING: {
            break;
        }
    }
}

Value::Value(const int initialValue) : currentType(ValueType::INT) {
    data = initialValue;
}

Value::Value(const double initialValue) : currentType(ValueType::DOUBLE) {
    data = initialValue;
}

Value::Value(const bool initialValue) : currentType(ValueType::BOOL) {
    data = initialValue;
}

Value::Value(const string& initialValue) : currentType(ValueType::STRING) {
    data = initialValue;
}

Value::Value(Value& other) {
    this->currentType = other.getType();

    switch (this->currentType) {
        case ValueType::INT: {
            this->data = other.getInt();
            break;
        }

        case ValueType::DOUBLE: {
            this->data = other.getDouble();
            break;
        }

        case ValueType::BOOL: {
            this->data = other.getBool();
            break;
        }

        case ValueType::STRING: {
            this->data = other.getString();
            break;
        }
    }

}

// Value::~Value() {
//     data.~variant();
// }

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
            return get<int>(data) != 0;
        }

        case ValueType::DOUBLE: {
            return get<double>(data) != 0;
        }

        case ValueType::BOOL: {
            return get<bool>(data);
        }

        case ValueType::STRING: {
            return !get<string>(data).empty();
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

    data = (int)newValue;
}

void Value::set(const double newValue) {
    this->currentType = ValueType::DOUBLE;

    data = (double)newValue;
}

void Value::set(const bool newValue) {
    this->currentType = ValueType::BOOL;

    data = (bool)newValue;
}

void Value::set(const string& newValue) {
    this->currentType = ValueType::STRING;

    data = newValue;
}

int Value::getInt() const {
    if (this->currentType == ValueType::INT && holds_alternative<int>(data)) {
        return get<int>(data);
    }

    throw runtime_error("Attept to access value as int, when type not int");
}

double Value::getDouble() const {
    if (this->currentType == ValueType::DOUBLE && holds_alternative<double>(data)) {
        return get<double>(data);
    }

    throw runtime_error("Attemt to access value as double, when type not double");
}

bool Value::getBool() const {
    if (this->currentType == ValueType::BOOL && holds_alternative<bool>(data)) {
        return get<bool>(data);
    }

    throw runtime_error("Attemtpt to access value as bool, when type not bool");
}

std::string Value::getString() const {
    if (this->currentType == ValueType::STRING && holds_alternative<string>(data)) {
        return get<string>(data);
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
            thisValue = get<double>(data);
        } else {
            thisValue = get<int>(data);
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
        return get<bool>(data) == other.getBool();
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
            thisValue = get<double>(data);
        } else {
            thisValue = get<int>(data);
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
            thisValue = get<double>(data);
        } else {
            thisValue = get<int>(data);
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
        return {get<int>(data) * other.getInt()};
    }

    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;

        if (this->currentType == ValueType::DOUBLE) {
            thisValue = get<double>(data);
        } else {
            thisValue = get<int>(data);
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
            data = other.getInt();
            break;

        case ValueType::DOUBLE:
            data = other.getDouble();
            break;

        case ValueType::BOOL:
            data = other.getBool();
            break;

        case ValueType::STRING:
            data = other.getString();
            break;
    }

    return *this;
}


Value Value::operator/(const Value& other) const {
    if (areBoth(ValueType::INT, *this, other)) {
        return {get<int>(data) / other.getInt()};
    }

    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;

        if (this->currentType == ValueType::DOUBLE) {
            thisValue = get<double>(data);
        } else {
            thisValue = get<int>(data);
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
        return {get<int>(data) - other.getInt()};
    }

    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;

        if (this->currentType == ValueType::DOUBLE) {
            thisValue = get<double>(data);
        } else {
            thisValue = get<double>(data);
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
        return {get<int>(data) + other.getInt()};
    }

    if (areBoth(ValueType::STRING, *this, other)) {
        return {get<string>(data) + other.getString()};
    }

    if (this->isNumeric() && other.isNumeric()) {
        double thisValue;
        double otherValue;

        if (this->currentType == ValueType::DOUBLE) {
            thisValue = get<double>(data);
        } else {
            thisValue = get<int>(data);
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

Environment::Environment() : enclosing(this) {}

Environment::Environment(Environment* enclosing) : enclosing(enclosing) {}

void Environment::define(const string& name, Value& value) {
    if (values.find(name) == values.end()) {
        values[name] = make_unique<Value>(value);
        return;
    }

    stringstream ss;
    ss << "Error declaring variable: " << name << "Variable with same name already exists" << endl;
    throw mash::RuntimeError(ss.str());
}

void Environment::assign(const Token& name, Value& value) {
    if (values.find(name.lexeme) != values.end()) {
        values[name.lexeme] = make_unique<Value>(value);
    } else if (enclosing != this) {
        enclosing->assign(name, value);
    }
    else {
        stringstream ss;
        ss << "Error assigning variable: " << name.lexeme << " is not defined in the current scope" << endl;
        throw mash::RuntimeError(ss.str());
    }
}

void Environment::assign(const std::string& name, Value& value) {
    if (values.find(name) != values.end()) {
        values[name] = make_unique<Value>(value);
    } else if (enclosing != this) {
        enclosing->assign(name, value);
    }
    else {
        stringstream ss;
        ss << "Error assigning variable: " << name << " is not defined in the current scope" << endl;
        throw mash::RuntimeError(ss.str());
    }
}

std::unique_ptr<Value>& Environment::get(const Token& name) {
    if (values.find(name.lexeme) != values.end()) {
        return values.at(name.lexeme);
    }

    if (enclosing != this) {
        return enclosing->get(name);
    }

    stringstream ss;
    ss << "Error accessing variable: " << name.lexeme << ", a variable with this name does not exist" << endl;
    throw mash::RuntimeError(ss.str());
}
