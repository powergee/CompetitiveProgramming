#include <iostream>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int a, b, x, y;
        scanf("%d %d %d %d", &a, &b, &x, &y);

        int answer = 0;
        answer = std::max(answer, a * y);
        answer = std::max(answer, b * x);
        answer = std::max(answer, a * b - b * x - b);
        answer = std::max(answer, a * b - a * y - a);
        printf("%d\n", answer);
    }

    return 0;
}