#include <iostream>
#include <map>

#include "int128.h"
#include "const.h"
#include "variable.h"
#include "add.h"
#include "subtract.h"
#include "multiply.h"
#include "divide.h"
#include "negate.h"

int main() {
    Int128 a(10);
    Int128 b(3);

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";

    std::cout << "a + b = " << (a + b) << "\n";
    std::cout << "a - b = " << (a - b) << "\n";
    std::cout << "a * b = " << (a * b) << "\n";
    std::cout << "a / b = " << (a / b) << "\n";

    Multiply mul(Const(2), Variable("x"));
    Add expr(mul, Const(1));

    std::map<std::string, Int128> vars;
    vars["x"] = Int128(100);

    Int128 result = expr.eval(vars);

    std::cout << "Expression: " << expr << "\n";
    std::cout << "Result: " << result << "\n";

    Negate neg(Const(42));
    std::cout << "Negate(42) = " << neg.eval(vars) << "\n";
}
