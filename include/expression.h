#pragma once

#include <map>
#include <string>
#include <iostream>
#include "int128.h"

class Expression {
public:
    virtual ~Expression() = default;

    virtual Int128 eval(const std::map<std::string, Int128>& vars) const = 0;
    virtual Expression* clone() const = 0;
    virtual void print(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Expression& expr);