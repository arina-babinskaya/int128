#include "negate.h"

Negate::Negate(const Expression& expr) : expr_(expr.clone()) {}

Negate::~Negate() {
    delete expr_;
}

Int128 Negate::eval(const std::map<std::string, Int128>& vars) const {
    return -expr_->eval(vars);
}

Expression* Negate::clone() const {
    return new Negate(*expr_);
}

void Negate::print(std::ostream& os) const {
    os << "-(";
    expr_->print(os);
    os << ")";
}