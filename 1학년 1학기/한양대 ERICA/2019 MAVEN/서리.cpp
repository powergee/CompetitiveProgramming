#include <iostream>
using namespace std;

typedef long long Long;

Long Factorial(int num)
{
    Long result = 1;

    for (int i = 2; i <= num; ++i)
        result *= i;

    return result;
}

Long Combination(int n, int k)
{
    if (n / 2 + (n % 2) <= k)
        k = n - k;

    Long result = 1;

    for (int i = n; i >= n-k+1; --i)
    {
        result *= i;
    }

    for (int i = 2; i <= k; ++i)
    {
        result /= i;
    }
    
    return result;
}

int main()
{
    int N, M;
    scanf("%d", &N);
    scanf("%d", &M);
    cout << Combination(M-1, M-N);

    return 0;
}