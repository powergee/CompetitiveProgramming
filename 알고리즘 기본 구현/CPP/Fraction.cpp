#include <cmath>
#include <algorithm>
#include <numeric>

typedef long long Long;

class Fraction {
private:
    Long num, den;

public:
    void reduce() {
        if (num == 0) {
            den = 1;
        } else {
            Long gcd = std::gcd(std::abs(num), std::abs(den));
            num /= gcd;
            den /= gcd;
            if ((num > 0) == (den > 0)) {
                num = std::abs(num);
                den = std::abs(den);
            } else if (num > 0) {
                num = -num;
                den = -den;
            }
        }
    }

    Fraction() : Fraction(0, 1) {}
    Fraction(Long n, Long d) : num(n), den(d) {
        reduce();
    }
    Fraction(Long value) : num(value), den(1) {}

    int toLong() const { return num / den; }
    double toDouble() const { return double(num) / den; }

    Fraction operator+() const {
        return Fraction(num, den);
    }

    Fraction operator-() const {
        return Fraction(-num, den);
    }

    Fraction operator+(const Fraction& f) const {
        return Fraction(num*f.den + f.num*den, den*f.den);
    }

    Fraction operator-(const Fraction& f) const {
        return Fraction(num*f.den - f.num*den, den*f.den);
    }

    Fraction operator*(const Fraction& f) const {
        return Fraction(num*f.num, den*f.den);
    }

    Fraction operator/(const Fraction& f) const {
        return Fraction(num*f.den, den*f.num);
    }

    bool operator<(const Fraction& f) const {
        return toDouble() < f.toDouble();
    }

    bool operator<=(const Fraction& f) const {
        return toDouble() <= f.toDouble();
    }

    bool operator>(const Fraction& f) const {
        return toDouble() > f.toDouble();
    }

    bool operator>=(const Fraction& f) const {
        return toDouble() >= f.toDouble();
    }

    bool operator==(const Fraction& f) const {
        return num == f.num && den == f.den;
    }

    bool operator!=(const Fraction& f) const {
        return num != f.num || den != f.den;
    }

    Long getNumerator() const {
        return num;
    }

    Long getDenominator() const {
        return den;
    }
};

template<typename T, typename std::enable_if_t<std::is_integral_v<T>>* = nullptr>
bool operator==(const Fraction& f, const T& other) {
    return f == Fraction(Long(other));
}

template<typename T, typename std::enable_if_t<std::is_integral_v<T>>* = nullptr>
bool operator!=(const Fraction& f, const T& other) {
    return f != Fraction(Long(other));
}