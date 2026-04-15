#include "subtract.h"

Subtract::Subtract(const Expression& l, const Expression& r) : l_(l.clone()), r_(r.clone()) {}

Subtract::~Subtract() {
    delete l_;
    delete r_;
}

Int128 Subtract::eval(const std::map<std::string, Int128>& vars) const {
    return l_->eval(vars) - r_->eval(vars);
}

Expression* Subtract::clone() const {
    return new Subtract(*l_, *r_);
}

void Subtract::print(std::ostream& os) const {
    os << "(";
    l_->print(os);
    os << " - ";
    r_->print(os);
    os << ")";
}