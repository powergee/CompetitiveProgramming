#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <vector>

typedef long long Long;

int n;
std::string expr;
Long dp[19];

Long Calc(Long a, Long b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0;
}

void GetVals(int right, std::vector<Long>& result)
{
    if (right == 0)
    {
        result.push_back(expr[0] - '0');
        return;
    }
    else if (right == 2)
    {
        result.push_back(Calc(expr[0] - '0', expr[2] - '0', expr[1]));
        return;
    }

    std::vector<Long> r1, r2;
    GetVals(right - 2, r1);
    GetVals(right - 4, r2);

    for (unsigned i = 0; i < r1.size(); ++i)
        r1[i] = Calc(r1[i], expr[right] - '0', expr[right - 1]);
    for (unsigned i = 0; i < r2.size(); ++i)
        r2[i] = Calc(r2[i], Calc(expr[right - 2] - '0', expr[right] - '0', expr[right - 1]), expr[right - 3]);

    result.insert(result.end(), r1.begin(), r1.end());
    result.insert(result.end(), r2.begin(), r2.end());
}

int main()
{
    std::cin >> n >> expr;
    std::fill(dp, dp + n, INT64_MIN);
    std::vector<Long> result;
    GetVals(n - 1, result);
    std::cout << *std::max_element(result.begin(), result.end());
}