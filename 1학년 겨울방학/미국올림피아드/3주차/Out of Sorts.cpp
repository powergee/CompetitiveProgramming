#include <iostream>
#include <algorithm>

int arr[100000];
int* ptrArr[100000];

bool PtrCompare(int*& p1, int*& p2)
{
    return *p1 < *p2;
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", (ptrArr[i] = arr + i));

    std::sort(ptrArr, ptrArr + n, PtrCompare);

    int count = 0;
    for (; count < n - 1; ++count)
    {
        if (ptrArr[count] > ptrArr[count + 1])
            break;
    }

    printf("%d", n - count);

    return 0;
}