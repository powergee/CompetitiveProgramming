#include <iostream>

int GetGCD(int u, int v)
{
    int t;

    while (v)
    {
        t = u % v;
        u = v;
        v = t;
    }

    return u;
}

class Fraction
{
private:
    int num = 0, den = 1;

public:
    Fraction(int n, int d);

    void Initialize(int n, int d);
    bool operator ==(const Fraction& f) const;
    bool operator <(const Fraction& f) const;
    bool operator >(const Fraction& f) const;
    bool operator <=(const Fraction& f) const;
    bool operator >=(const Fraction& f) const;

    Fraction operator+(const Fraction& f) const;
    Fraction operator-(const Fraction& f) const;
    Fraction operator*(const Fraction& f) const;
    Fraction operator/(const Fraction& f) const;

    int GetNumerator() const;
    int GetDenomiator() const;

    double ToDouble() const;
};

Fraction::Fraction(int n, int d)
{
    Initialize(n, d);
}

void Fraction::Initialize(int n, int d)
{
    int gcd = GetGCD(n, d);
    num = n / gcd;
    den = d / gcd;
}

bool Fraction::operator==(const Fraction &f) const
{
    return num == f.num && den == f.den;
}

bool Fraction::operator<(const Fraction &f) const
{
    return ToDouble() < f.ToDouble();
}

bool Fraction::operator>(const Fraction &f) const
{
    return ToDouble() > f.ToDouble();
}

bool Fraction::operator<=(const Fraction &f) const
{
    return ToDouble() < f.ToDouble() || *this == f;
}

bool Fraction::operator>=(const Fraction &f) const
{
    return ToDouble() > f.ToDouble() || *this == f;
}

Fraction Fraction::operator+(const Fraction &f) const
{
    return Fraction(num*f.den + f.num*den, den * f.den);
}

Fraction Fraction::operator-(const Fraction &f) const
{
    return Fraction(num*f.den - f.num*den, den * f.den);
}

Fraction Fraction::operator*(const Fraction &f) const
{
    return Fraction(num*f.num, den*f.den);
}

Fraction Fraction::operator/(const Fraction &f) const
{
    return Fraction(num*f.den, den*f.num);
}

int Fraction::GetNumerator() const
{
    return num;
}

int Fraction::GetDenomiator() const
{
    return den;
}

double Fraction::ToDouble() const
{
    return (double)(num) / den;
}

int main()
{
    int n1 = 10, d1 = 31;
    int n2 = 100, d2 = 310;
    int n3 = 1310, d3 = 4061;
    int n4 = 1101, d4 = 53;

    Fraction f1(n1, d1);
    Fraction f2(n2, d2);
    Fraction f3(n3, d3);
    Fraction f4(n4, d4);

    printf("f1: %d/%d (%lf)\n", f1.GetNumerator(), f1.GetDenomiator(), f1.ToDouble());
    printf("f2: %d/%d (%lf)\n", f2.GetNumerator(), f2.GetDenomiator(), f2.ToDouble());
    printf("f3: %d/%d (%lf)\n", f3.GetNumerator(), f3.GetDenomiator(), f3.ToDouble());
    printf("f4: %d/%d (%lf)\n", f4.GetNumerator(), f4.GetDenomiator(), f4.ToDouble());

    printf("f1 == f2: %s\n", (f1 == f2 ? "True" : "False"));
    printf("f2 == f3: %s\n", (f2 == f3 ? "True" : "False"));
    printf("f3 == f1: %s\n", (f3 == f1 ? "True" : "False"));

    Fraction add = f1 + f4;
    Fraction sub = f1 - f4;
    Fraction mul = f1 * f4;
    Fraction div = f1 / f4;
    printf("f1 + f4 = %d/%d (%lf)\n", add.GetNumerator(), add.GetDenomiator(), add.ToDouble());
    printf("f1 - f4 = %d/%d (%lf)\n", sub.GetNumerator(), sub.GetDenomiator(), sub.ToDouble());
    printf("f1 * f4 = %d/%d (%lf)\n", mul.GetNumerator(), mul.GetDenomiator(), mul.ToDouble());
    printf("f1 / f4 = %d/%d (%lf)\n", div.GetNumerator(), div.GetDenomiator(), div.ToDouble());

    return 0;
}