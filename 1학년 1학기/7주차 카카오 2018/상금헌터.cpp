#include <iostream>
using namespace std;

int TC;
int a, b;

int GetFirst(int grade)
{
    if (grade == 1)
        return 5000000;
    else if (grade >= 2 && grade <= 3)
        return 3000000;
    else if (grade >= 4 && grade <= 6)
        return 2000000;
    else if (grade >= 7 && grade <= 10)
        return 500000;
    else if (grade >= 11 && grade <= 15)
        return 300000;
    else if (grade >= 16 && grade <= 21)
        return 100000;
    else return 0;
}

int GetSecond(int grade)
{
    if (grade == 1)
        return 5120000;
    else if (grade >= 2 && grade <= 3)
        return 2560000;
    else if (grade >= 4 && grade <= 7)
        return 1280000;
    else if (grade >= 8 && grade <= 15)
        return 640000;
    else if (grade >= 16 && grade <= 31)
        return 320000;
    else return 0;
}

int main()
{
    scanf("%d", &TC);

    while (TC--)
    {
        scanf("%d %d", &a, &b);

        printf("%d\n", GetFirst(a) + GetSecond(b));
    }
}