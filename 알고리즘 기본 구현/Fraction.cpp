#include <cmath>
#include <algorithm>

typedef long long Long;

class Fraction
{
private:
    Long num, den;

public:
    Fraction(Long n, Long d) : num(n), den(d) {}
    Fraction() : Fraction(0, 1) {}

    void reduce()
    {
        if (num == 0)
            den = 1;
        else
        {
            Long min = std::min(num, den);

            if (num % min == 0 && den % min == 0)
                num /= min, den /= min;
            else
                for (int i = 2; i <= sqrt(min); ++i)
                    if (num % i == 0 && den % i == 0)
                        num /= i, den /= i, --i;
        }
    }

    int toInt()
    {
        return num / den;
    }

    double toDouble()
    {
        return (double)num / den;
    }

    Fraction operator+()
    {
        return Fraction(num, den);
    }

    Fraction operator-()
    {
        return Fraction(-num, den);
    }

    Fraction operator+(Fraction f)
    {
        return Fraction(num*f.den + f.num*den, den*f.den);
    }

    Fraction operator-(Fraction f)
    {
        return Fraction(num*f.den - f.num*den, den*f.den);
    }

    Fraction operator*(Fraction f)
    {
        return Fraction(num*f.num, den*f.den);
    }

    Fraction operator/(Fraction f)
    {
        return Fraction(num*f.den, den*f.num);
    }

    bool operator<(Fraction f)
    {
        return toDouble() < f.toDouble();
    }

    bool operator<=(Fraction f)
    {
        return toDouble() <= f.toDouble();
    }

    bool operator>(Fraction f)
    {
        return toDouble() > f.toDouble();
    }

    bool operator>=(Fraction f)
    {
        return toDouble() >= f.toDouble();
    }

    Long getNumerator()
    {
        return num;
    }

    Long getDenominator()
    {
        return den;
    }
};