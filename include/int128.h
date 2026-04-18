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
    explicit Int128(std::string_view str);

    explicit operator int64_t() const ;
    explicit operator double() const ;

    std::string str() const;

    Int128& operator+=(const Int128& other);
    Int128& operator-=(const Int128& other);
    Int128& operator*=(const Int128& other);
    Int128& operator/=(const Int128& other);

    Int128 operator+(const Int128& other) const;
    Int128 operator-(const Int128& other) const;
    Int128 operator*(const Int128& other) const;
    Int128 operator/(const Int128& other) const;

    Int128 operator-() const;

    bool operator==(const Int128& other);
    bool operator!=(const Int128& other);

    friend std::ostream& operator<<(std::ostream&, const Int128&);

    bool operator<(const Int128& other);
    bool operator<=(const Int128& other);

    bool operator>(const Int128& other);
    bool operator>=(const Int128& other);

    Int128 operator<<(int shift) const;
    Int128& operator<<=(int shift);

    Int128 operator>>(int shift) const;
    Int128& operator>>=(int shift);
};