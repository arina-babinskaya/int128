#include "divide.h"

Divide::Divide(const Expression& l, const Expression& r) : l_(l.clone()), r_(r.clone()) {}

Divide::~Divide() {
    delete l_;
    delete r_;
}

Int128 Divide::eval(const std::map<std::string, Int128>& vars) const {
    return l_->eval(vars) / r_->eval(vars);
}

Expression* Divide::clone() const {
    return new Divide(*l_, *r_);
}

void Divide::print(std::ostream& os) const {
    os << "(";
    l_->print(os);
    os << " / ";
    r_->print(os);
    os << ")";
}