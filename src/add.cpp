#include "add.h"

Add::Add(const Expression& l, const Expression& r) : l_(l.clone()), r_(r.clone()) {}

Add::~Add() {
    delete l_;
    delete r_;
}

Int128 Add::eval(const std::map<std::string, Int128>& vars) const {
    return l_->eval(vars) + r_->eval(vars);
}

Expression* Add::clone() const {
    return new Add(*l_, *r_);
}

void Add::print(std::ostream& os) const {
    os << "(";
    l_->print(os);
    os << " + ";
    r_->print(os);
    os << ")";
}