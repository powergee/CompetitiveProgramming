#include <iostream>
#include <vector>

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
    int num, den;

public:
    Fraction() : num(0), den(1) {}
    Fraction(int n, int d);

    void Initialize(int n, int d);
    bool operator ==(const Fraction& f) const;

    Fraction operator+(const Fraction& f) const;
    Fraction operator-(const Fraction& f) const;
    Fraction operator*(const Fraction& f) const;
    Fraction operator/(const Fraction& f) const;

    int GetNumerator() const;
    int GetDenomiator() const;

    double ToDouble() const;
    int ToInt() const;
    bool IsInt() const;
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
    return abs(num) == abs(f.num) && abs(den) == abs(f.den) && ((ToDouble() > 0) == (f.ToDouble() > 0));
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

int Fraction::ToInt() const
{
    return num / den;
}

bool Fraction::IsInt() const
{
    return abs(num) % abs(den) == 0;
}

void PrintMatrix(std::vector<std::vector<Fraction>>& matrix)
{
    for (auto row : matrix)
    {
        for (auto ele : row)
        {
            printf("%.2lf\t", ele.ToDouble());
        }
        printf("\n");
    }
    printf("\n");
}

void ToRREF(std::vector<std::vector<Fraction>>& matrix)
{
    int lead = 0;
    int rowCount = matrix.size();
    int colCount = matrix[0].size();

    for (int r = 0; r < rowCount; ++r)
    {
        if (colCount <= lead)
            break;
        
        int i = r;
        while (matrix[i][lead].GetNumerator() == 0)
        {
            ++i;
            if (rowCount == i)
            {
                i = r;
                ++lead;
                if (colCount == lead)
                {
                    --lead;
                    break;
                }
            }
        }

        for (int c = 0; c < colCount; ++c)
            std::swap(matrix[i][c], matrix[r][c]);

        if (matrix[r][lead].GetNumerator() != 0)
        {
            Fraction div = matrix[r][lead];
            for (int c = 0; c < colCount; ++c)
                matrix[r][c] = matrix[r][c] / div;
        }
        
        for (i = 0; i < rowCount; ++i)
        {
            if (i != r)
            {
                Fraction sub = matrix[i][lead];
                for (int k = 0; k < colCount; ++k)
                    matrix[i][k] = matrix[i][k] - (sub * matrix[r][k]);
            }
        }
        ++lead;
    }
}

int N;
std::vector<int> arr;
std::vector<std::vector<Fraction>> matrix;

int main()
{
    scanf("%d", &N);
    arr.resize(N);

    for (int i = 0; i < N; ++i)
        scanf("%d", &arr[i]);

    if (N == 1)
        printf("A");
    else
    {
        for (int i = 0; i < N - 1; ++i)
        {
            matrix.emplace_back(3);
            matrix[i][0] = Fraction(arr[i], 1);
            matrix[i][1] = Fraction(1, 1);
            matrix[i][2] = Fraction(arr[i + 1], 1);
        }

        ToRREF(matrix);

        bool isPivotCol[3] { false, false, false };
        for (int r = 0; r < (int)matrix.size(); ++r)
        {
            int p;
            for (p = 0; p < 3; ++p)
                if (matrix[r][p].GetNumerator() != 0)
                    break;
            
            if (p != 3)
                isPivotCol[p] = true;
        }

        if (isPivotCol[2])
            printf("B");
        else if (isPivotCol[0] && isPivotCol[1])
        {
            if (matrix[0][2].IsInt() && matrix[1][2].IsInt())
                printf("%d", (Fraction(arr[N - 1], 1) * matrix[0][2] + matrix[1][2]).ToInt());
            else printf("B");
        }
        else if (matrix[0][0] == matrix[0][2])
            printf("%d", (matrix[0][2] / matrix[0][1]).ToInt());
        else printf("A");
    }

    return 0;
}