#include "int128.h"
#include <algorithm>
#include <string>
#include <string_view>

Int128::Int128() : high_(0), low_(0) {}
Int128::Int128(int64_t v) : low_(v) {
    if (v < 0) { high_ = -1; } 
    else { high_ = 0; }
}

Int128::operator int64_t() const {
    return static_cast<int64_t>(low_);
}

Int128::operator double() const {
    return std::ldexp(static_cast<double>(high_), 64) + static_cast<double>(low_);
}

std::string Int128::str() const {
    if (*this == Int128(0)) { return "0"; }
    Int128 temp = *this;
    bool neg = temp.high_ < 0;
    if (neg) { temp = -temp; } // not to have problems with /

    std::string s; 
    while (temp != Int128(0)) {
        Int128 q = temp / Int128(10);
        Int128 r = temp - q * Int128(10); // for not to write operator %
        int64_t digit = static_cast<int64_t>(r);
        s.push_back('0' + digit);
        temp = q;
    }

    if (neg) { s.push_back('-'); }
    std::reverse(s.begin(), s.end());
    return s;
}

Int128& Int128::operator+=(const Int128& other) {
    uint64_t old = low_;
    low_ += other.low_;
    high_ += other.high_;

    if (low_ < old) { high_ += 1; }
    return *this;
}

Int128& Int128::operator-=(const Int128& other) {
    uint64_t old = low_;
    low_ -= other.low_;
    high_ -= other.high_;

    if (low_ > old) { high_ -= 1; }
    return *this;
}

Int128 Int128::operator-() const {
    return Int128(0) - *this;
}

Int128& Int128::operator*=(const Int128& other) {
    uint64_t al = static_cast<uint32_t>(low_); 
    uint64_t ah = low_ >> 32;
    uint64_t bl = static_cast<uint32_t>(other.low_); 
    uint64_t bh = other.low_ >> 32;

    uint64_t p0 = al * bl;
    uint64_t p1 = al * bh;
    uint64_t p2 = ah * bl;
    uint64_t p3 = ah * bh;

    uint64_t middle = (p0 >> 32) + static_cast<uint32_t>(p1) + p2;
    
    uint64_t new_low = (middle << 32) | static_cast<uint32_t>(p0);
    uint64_t new_high = p3 + (middle >> 32) + (p1 >> 32);

    new_high += (static_cast<uint64_t>(high_) * other.low_) + (low_ * static_cast<uint64_t>(other.high_));

    low_ = new_low;
    high_ = static_cast<int64_t>(new_high);
    
    return *this;
}


Int128& Int128::operator/=(const Int128& other) {
    bool neg = (high_ < 0) ^ (other.high_ < 0);

    Int128 dividend = *this;
    Int128 divisor = other;

    if (dividend.high_ < 0) dividend = -dividend;
    if (divisor.high_ < 0) divisor = -divisor;

    Int128 quotient(0);
    Int128 remainder(0);

    for (int i = 127; i >= 0; --i) {

        remainder = remainder * Int128(2);

        if (i >= 64) {
            remainder.low_ |= (dividend.high_ >> (i - 64)) & 1;
        } else {
            remainder.low_ |= (dividend.low_ >> i) & 1;
        }

        if (!(remainder < divisor)) {
            remainder -= divisor;

            if (i >= 64) {
                quotient.high_ |= (1ULL << (i - 64));
            } else {
                quotient.low_ |= (1ULL << i);
            }
        }
    }

    if (neg) quotient = -quotient;

    *this = quotient;
    return *this;
}

bool operator==(const Int128& a,const Int128& b) { return a.high_ == b.high_ && a.low_ == b.low_; }

bool operator!=(const Int128& a,const Int128& b){ return !(a == b); } 

std::ostream& operator<<(std::ostream& os,const Int128& v) {
    os << v.str();
    return os;
}

Int128 operator+(Int128 a,const Int128& b){return a+=b;}

Int128 operator-(Int128 a,const Int128& b){return a-=b;}

Int128 operator*(Int128 a,const Int128& b){return a*=b;}

Int128 operator/(Int128 a,const Int128& b){return a/=b;}

bool operator<(const Int128& a, const Int128& b) {
    if (a.high_ != b.high_) return a.high_ < b.high_;
    return a.low_ < b.low_;
}

bool operator>=(const Int128& a, const Int128& b) {
    return !(a < b);
}
