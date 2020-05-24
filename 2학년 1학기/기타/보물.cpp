#include <iostream>
#include <algorithm>
#include <functional>

int a[50], b[50];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);

    for (int i = 0; i < n; ++i)
        scanf("%d", b + i);

    std::sort(a, a + n);
    std::sort(b, b + n, std::greater<int>());

    int result = 0;
    for (int i = 0; i < n; ++i)
        result += a[i] * b[i];

    printf("%d", result);

    return 0;
}