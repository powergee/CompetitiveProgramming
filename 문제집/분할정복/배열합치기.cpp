#include <iostream>
#include <algorithm>

int arr1[1000001];
int arr2[1000001];
int merged[2000000];

int main()
{
    std::fill(arr1, arr1 + 1000001, 0x7fffffff);
    std::fill(arr2, arr2 + 1000001, 0x7fffffff);

    int n, m;
    scanf("%d %d", &n, &m);

    int input;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &input);
        arr1[i] = input;
    }

    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &input);
        arr2[i] = input;
    }

    int i1 = 0, i2 = 0, pos = 0;
    while (i1 < n || i2 < m)
    {
        if (arr1[i1] > arr2[i2])
            merged[pos++] = arr2[i2++];
        else merged[pos++] = arr1[i1++];
    }

    for (int i = 0; i < n + m; ++i)
    {
        printf("%d ", merged[i]);
    }

    return 0;
}