#include <iostream>
#include <algorithm>
#include <functional>

// 열량 / 가격
typedef std::pair<int, int> Frac;

int topping[100];

double Calc(std::pair<int, int> fr)
{
    return (double)fr.first / fr.second;
}

int main()
{
    int N, A, B, C;
    scanf("%d", &N);
    scanf("%d %d", &A, &B);
    scanf("%d", &C);

    for (int i = 0; i < N; ++i)
        scanf("%d", topping + i);

    std::sort(topping, topping + N, std::greater<int>());

    Frac prev = {C, A}, now;

    for (int i = 0; i < N; ++i)
    {
        now = {prev.first + topping[i], prev.second + B};
        if (Calc(prev) >= Calc(now))
            break;

        prev = now;
    }

    printf("%d", prev.first / prev.second);

    return 0;
}