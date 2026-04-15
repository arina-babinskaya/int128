#pragma once

#include "expression.h"

class Negate : public Expression {
private:
    Expression* expr_;

public:
    explicit Negate(const Expression& expr);
    ~Negate();

    Int128 eval(const std::map<std::string, Int128>& vars) const override;
    Expression* clone() const override;
    void print(std::ostream& os) const override;
};