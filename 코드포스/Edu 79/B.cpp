#include <iostream>
#include <algorithm>

int times[100001];
int n, s;

// return: 부른 노래의 개수, 스킵한 노래 순서
std::pair<int, int> TryToSing(int remain, int index, bool skip)
{
    if (remain == 0 || index >= n)
        return {0, 0};

    std::pair<int, int> result = {-1, 0};
    std::pair<int, int> current;

    if (skip)
    {
        current = TryToSing(remain, index + 1, false);
        current.second = index + 1;
        if (current.first > result.first)
            result = current;
    }

    if (remain >= times[index])
    {
        current = TryToSing(remain - times[index], index + 1, skip);
        ++current.first;
        if (current.first > result.first)
            result = current;
    }

    return result;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d %d", &n, &s);

        for (int i = 0; i < n; ++i)
            scanf("%d", times + i);

        std::pair<int, int> result = TryToSing(s, 0, true);
        printf("%d\n", result.second);
    }
}