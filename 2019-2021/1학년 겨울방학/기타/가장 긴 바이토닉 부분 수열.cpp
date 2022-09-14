#include <iostream>
#include <algorithm>

int n;
int asc[1000];
int des[1000];
int arr[1000];

int GetAscCount(int last)
{
    int& result = asc[last];
    if (result != -1)
        return result;

    result = 1;
    for (int i = last - 1; i >= 0; --i)
        if (arr[i] < arr[last])
            result = std::max(result, GetAscCount(i) + 1);

    return result;
}

int GetDesCount(int first)
{
    int& result = des[first];
    if (result != -1)
        return result;
    
    result = 1;
    for (int i = first + 1; i < n; ++i)
        if (arr[first] > arr[i])
            result = std::max(result, GetDesCount(i) + 1);

    return result;
}

int main()
{
    scanf("%d", &n);

    std::fill(asc, asc + n, -1);
    std::fill(des, des + n, -1);
    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);

    int result = -1;
    for (int i = 0; i < n; ++i)
        result = std::max(result, GetAscCount(i) + GetDesCount(i) - 1);

    printf("%d", result);

    return 0;
}