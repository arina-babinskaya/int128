#include "int128.h"
#include <algorithm>
#include <string>
#include <string_view>

Int128::Int128() : high_(0), low_(0) {}

Int128::Int128(int64_t v) : low_(v) {
    if (v < 0) { high_ = -1; } 
    else { high_ = 0; }
}

Int128::Int128(std::string_view str) : high_(0), low_(0) {
    bool neg = false;
    size_t start = 0;
    if (str[0] == '-') {
        neg = true;
        start = 1;
    }

    for (size_t i = start; i < str.size(); ++i) {
        *this *= Int128(10);
        *this += Int128(str[i] - '0');
    }

    if (neg) {
        *this = -*this;
    }
}

Int128::operator int64_t() const {
    return static_cast<int64_t>(low_);
}

Int128::operator double() const {
    double high = std::ldexp(static_cast<double>(high_), 64);
    double low = static_cast<double>(static_cast<uint64_t>(low_));
    return high + low;
}

std::string Int128::str() const {
    if (high_ == 0 && low_ == 0) { return "0"; }
    Int128 temp = *this;
    bool neg = temp.high_ < 0;
    if (neg) { temp = -temp; } // not to have problems with /

    std::string s; 
    while (temp != Int128(0)) {
        Int128 q = temp / Int128(10);
        Int128 r = temp - q * Int128(10); // for not to write operator %
        int digit = static_cast<int>(static_cast<uint64_t>(r.low_));
        s.push_back('0' + digit);
        temp = q;
    }

    if (neg) { s.push_back('-'); }
    std::reverse(s.begin(), s.end());
    return s;
}

Int128& Int128::operator+=(const Int128& other) {
    uint64_t old_low = low_;
    low_ += other.low_;

    uint64_t carry = (low_ < old_low);

    uint64_t new_high = static_cast<uint64_t>(high_) + static_cast<uint64_t>(other.high_) + carry;
    high_ = static_cast<int64_t>(new_high);

    return *this;
}

Int128& Int128::operator-=(const Int128& other) {
    *this += (-other);
    return *this;
}

Int128& Int128::operator*=(const Int128& other) {
    Int128 result(0);
    Int128 l = *this;
    Int128 r = other;

    bool neg = false;

    if (l.high_ < 0) {
        l = -l;
        neg = !neg;
    }
    if (r.high_ < 0) {
        r = -r;
        neg = !neg;
    }

    while (r != Int128(0)) {
        if ((r.low_ & 1) != 0) {
            result += l;
        }
        l += l;
        r >>= 1;
    }

    if (neg) { result = -result; }

    *this = result;
    return *this;
}

Int128& Int128::operator/=(const Int128& other) {
    bool neg = false;

    Int128 result(0);
    Int128 l = *this;
    Int128 r = other;

    if (l.high_ < 0) {
        l = -l;
        neg = !neg;
    }
    if (r.high_ < 0) {
        r = -r;
        neg = !neg;
    }

    while (r <= l) {
        Int128 temp = r;
        Int128 temp2 = Int128(1);

        while ((temp << 1) <= l) {
            temp <<= 1;
            temp2 <<= 1;
        }

        l -= temp;
        result += temp2;
    }

    if (neg) { result = -result; }

    *this = result;
    return *this;
}

Int128 Int128::operator+(const Int128& other) const {
    Int128 temp = *this;
    temp += other;
    return temp;
}

Int128 Int128::operator-(const Int128& other) const {
    Int128 temp = *this;
    temp -= other;
    return temp;
}
Int128 Int128::operator*(const Int128& other) const {
    Int128 temp = *this;
    temp *= other;
    return temp;
}
Int128 Int128::operator/(const Int128& other) const {
    Int128 temp = *this;
    temp /= other;
    return temp;
}

Int128 Int128::operator-() const {
    Int128 result;
    result.low_ = ~low_;
    result.high_ = ~high_;
    result += Int128(1);
    return result;
}

bool Int128::operator==(const Int128& other) { return high_ == other.high_ && low_ == other.low_; }
bool Int128::operator!=(const Int128& other) { return !(*this == other); } 

std::ostream& operator<<(std::ostream& os, const Int128& v) { return os << v.str(); }

bool Int128::operator<(const Int128& other) {
    if (high_ != other.high_) { return high_ < other.high_; }
    return low_ < other.low_;
}

bool Int128::operator<=(const Int128& other) {
    return *this < other || *this == other;
}

bool Int128::operator>(const Int128 &other) {
    if (high_ != other.high_) { return other.high_ < high_; }
    return other.low_ < low_;
}
bool Int128::operator>=(const Int128 &other) {
    return *this > other || *this == other;
}

Int128& Int128::operator<<=(int shift) {
    if (shift >= 128) {
        high_ = 0;
        low_ = 0;
        return *this;
    }

    if (shift >= 64) {
        high_ = static_cast<int64_t>(low_ << (shift - 64));
        low_ = 0;
    } else if (shift > 0) {
        high_ = (high_ << shift) | (low_ >> (64 - shift));
        low_ <<= shift;
    }
    return *this;
}

Int128 Int128::operator<<(int shift) const {
    Int128 temp = *this;
    temp <<= shift;
    return temp;
}

Int128& Int128::operator>>=(int shift) {
    if (shift >= 128) {
        if (high_ < 0) {  high_ = -1; }
        else { high_ = 0; }
        low_ = 0;
        return *this;
    }

    if (shift >= 64) {
        low_ = static_cast<uint64_t>(high_ >> (shift - 64));
        if (high_ < 0) {  high_ = -1; }
        else { high_ = 0; }
    } else if (shift > 0) {
        low_ = (low_ >> shift) | (static_cast<uint64_t>(high_) << (64 - shift));
        high_ >>= shift;
    }
    return *this;
}

Int128 Int128::operator>>(int shift) const {
    Int128 temp = *this;
    temp >>= shift;
    return temp;
}