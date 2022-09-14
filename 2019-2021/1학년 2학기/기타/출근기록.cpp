#include <iostream>
#include <string>
#define A 0
#define B 1
#define C 2

std::string input;
int count[3];
bool impossible[51][51][51][3][3];
char result[51];

bool Find(int a, int b, int c, int prev2, int prev1)
{
    if (impossible[a][b][c][prev2][prev1])
        return false;

    if (a == 0 && b == 0 && c == 0)
        return true;

    if (prev2 != C && prev1 != C && c > 0)
    {
        if (Find(a, b, c - 1, prev1, C))
        {
            result[input.size() - a - b - c] = 'C';
            return true;
        }
    }

    if (prev1 != B && b > 0)
    {
        if (Find(a, b - 1, c, prev1, B))
        {
            result[input.size() - a - b - c] = 'B';
            return true;
        }
    }

    if (a > 0)
    {
        if (Find(a - 1, b, c, prev1, A))
        {
            result[input.size() - a - b - c] = 'A';
            return true;
        }
    }

    impossible[a][b][c][prev2][prev1] = true;
    return false;
}

int main()
{
    std::cin >> input;

    for (char ch : input)
        ++count[ch - 'A'];

    result[input.size()] = '\0';

    if (Find(count[0], count[1], count[2], A, A))
        printf("%s", result);
    else printf("-1");

    return 0;
}