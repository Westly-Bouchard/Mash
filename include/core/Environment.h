//
// Created by Westly Bouchard on 12/4/23.
//

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <unordered_map>

#include "Token.h"

#define VALUE_TYPE std::variant<int, double, bool, std::string>

enum class ValueType {
    INT, DOUBLE, BOOL, STRING
};

class Value {
public:
    Value();
    Value(ValueType kind, int initialValue);
    Value(ValueType kind, double initialValue);
    Value(ValueType kind, bool initialValue);
    Value(ValueType kind, const std::string& initialValue);

    Value(Value& other);

    ~Value();

    ValueType getType() const;

    bool isOfType(ValueType kind) const;

    bool sameTypeAs(const Value& other) const;

    bool isTruthy() const;

    bool isNumeric() const;

    static bool areSameType(const Value& one, const Value& two);
    static bool areBoth(ValueType kind, const Value& one, const Value& two);

    void set(int newValue);
    void set(double newValue);
    void set(bool newValue);
    void set(const std::string& newValue);

    int getInt() const;
    double getDouble() const;
    bool getBool() const;
    std::string getString() const;

    bool operator==(const Value& other) const;
    bool operator!=(const Value& other) const;
    bool operator<=(const Value& other) const;
    bool operator>=(const Value& other) const;
    bool operator<(const Value& other) const;
    bool operator>(const Value& other) const;


private:
    ValueType currentType;

    union {
        int asInt;
        double asDouble;
        bool asBool;
        std::string asString;
    };
};

class Environment {
public:
    Environment() = default;

    void define(const std::string& name, Value& value);

    std::unique_ptr<Value>& get(const Token& name);

private:
    std::unordered_map<std::string, std::unique_ptr<Value>> values;
};



#endif //ENVIRONMENT_H
