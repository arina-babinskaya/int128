#include "expression.h"

std::ostream& operator<<(std::ostream& os, const Expression& expr) {
    expr.print(os);
    return os;
}