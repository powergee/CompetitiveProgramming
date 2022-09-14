#include <iostream>

// 한 막대의 길이가 stick일 때, stick보다 짧거나 같은 길이들 중 가장 큰 2의 제곱수 반환
inline int GetMaxLength(int stick)
{
    for (int i = 0; ; ++i)
    {
        if (1<<i > stick)
            return 1<<(i-1);
    }

    // 도달할 일 없음.
    return 0;
}

int main()
{
    int x;
    scanf("%d", &x);

    int count = 0;
    while (x)
    {
        x -= GetMaxLength(x);
        ++count;
    }

    printf("%d", count);

    return 0;
}