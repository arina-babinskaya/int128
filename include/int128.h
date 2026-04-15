#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <iostream>

class Int128 {
private:
    int64_t high_; 
    uint64_t low_;

public:

    Int128();
    Int128(int64_t v);

    explicit operator int64_t() const ;
    explicit operator double() const ;

    std::string str() const;

    Int128& operator+=(const Int128& other);
    Int128& operator-=(const Int128& other);
    Int128& operator*=(const Int128& other);
    Int128& operator/=(const Int128& other);

    Int128 operator-() const;

    friend bool operator==(const Int128&, const Int128&);
    friend bool operator!=(const Int128&, const Int128&);
    friend bool operator<(const Int128& a, const Int128& b);

    friend std::ostream& operator<<(std::ostream&, const Int128&);
};

Int128 operator+(Int128, const Int128&);
Int128 operator-(Int128, const Int128&);
Int128 operator*(Int128, const Int128&);
Int128 operator/(Int128, const Int128&);
