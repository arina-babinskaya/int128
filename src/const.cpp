#include "const.h"

Const::Const(Int128 value) : value_(value) {}

Int128 Const::eval(const std::map<std::string, Int128>&) const {
    return value_;
}

Expression* Const::clone() const {
    return new Const(value_);
}

void Const::print(std::ostream& os) const {
    os << value_;
}