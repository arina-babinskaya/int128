#include "multiply.h"

Multiply::Multiply(const Expression& l, const Expression& r) : l_(l.clone()), r_(r.clone()) {}

Multiply::~Multiply() {
    delete l_;
    delete r_;
}

Int128 Multiply::eval(const std::map<std::string, Int128>& vars) const {
    return l_->eval(vars) * r_->eval(vars);
}

Expression* Multiply::clone() const {
    return new Multiply(*l_, *r_);
}

void Multiply::print(std::ostream& os) const {
    os << "(";
    l_->print(os);
    os << " * ";
    r_->print(os);
    os << ")";
}