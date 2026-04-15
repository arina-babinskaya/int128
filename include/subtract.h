#pragma once

#include "expression.h"

class Subtract : public Expression {
private:
    Expression* l_;
    Expression* r_;

public:
    Subtract(const Expression& l, const Expression& r);
    ~Subtract();

    Int128 eval(const std::map<std::string, Int128>& vars) const override;
    Expression* clone() const override;
    void print(std::ostream& os) const override;
};