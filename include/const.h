#pragma once

#include "expression.h"

class Const : public Expression {
private:
    Int128 value_;

public:
    explicit Const(Int128 value);

    Int128 eval(const std::map<std::string, Int128>&) const override;
    Expression* clone() const override;
    void print(std::ostream&) const override;
};