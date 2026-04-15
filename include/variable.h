#pragma once

#include "expression.h"

class Variable : public Expression {
private:
    std::string name_;

public:
    explicit Variable(std::string name);

    Int128 eval(const std::map<std::string, Int128>& vars) const override;
    Expression* clone() const override;
    void print(std::ostream&) const override;
};