#include <iostream>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using Long = long long;

template<typename T>
using OrderedSet = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
    long double toDouble() const { return (long double)(num) / den; }

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

int main() {
    int q;
    scanf("%d", &q);

    OrderedSet<std::pair<Fraction, int>> posInter, negInter;
    bool alwaysZero = false;
    bool flip = false;

    while (q--) {
        int comm;
        scanf("%d", &comm);
        if (comm == 1) {
            Long a, b;
            scanf("%lld %lld", &a, &b);

            if (a == 0 && b == 0) {
                alwaysZero = true;
            } else if (a == 0) {
                if (b < 0) {
                    flip = !flip;
                }
            } else {
                Fraction inter(-b, a);
                (a > 0 ? posInter : negInter).insert({inter, q});
            }
        } else {
            Long c;
            scanf("%lld", &c);

            if (alwaysZero) {
                printf("0\n");
                continue;
            }
            if (posInter.size() == 0 && negInter.size() == 0) {
                printf(flip ? "-\n" : "+\n");
                continue;
            }

            auto posIt = posInter.lower_bound({Fraction(c), 0});
            auto negIt = negInter.lower_bound({Fraction(c), 0});

            if ((posIt != posInter.end() && posIt->first == c) || (negIt != negInter.end() && negIt->first == c)) {
                printf("0\n");
                continue;
            }

            int negCount = (posIt == posInter.end() ? 0 : posInter.size() - posInter.order_of_key(*posIt))
                         + (negIt == negInter.end() ? negInter.size() : negInter.order_of_key(*negIt));
            bool negEven = (negCount % 2 == 0);
            if (flip) {
                negEven = !negEven;
            }
            printf(negEven ? "+\n" : "-\n");
        }
    }

    return 0;
}