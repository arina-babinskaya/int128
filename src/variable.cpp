#include "variable.h"

Variable::Variable(std::string name) : name_(std::move(name)) {}

Int128 Variable::eval(const std::map<std::string, Int128>& vars) const {
    return vars.at(name_);
}

Expression* Variable::clone() const {
    return new Variable(name_);
}

void Variable::print(std::ostream& os) const {
    os << name_;
}