#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

typedef long long Long;

int arr[200000];
int leftCount[200000];
int rightCount[200000];

bool IsPer(int* arr, int start, int end)
{
    std::vector<int> copy(arr + start, arr + end + 1);
    std::sort(copy.begin(), copy.end());

    for (int i = 0; i < end - start + 1; ++i)
    {
        if (i + 1 != copy[i])
            return false;
    }
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", arr + i);

        std::fill(leftCount, leftCount + n, 0);
        std::fill(rightCount, rightCount + n, 0);

        std::set<std::pair<int, int>> answer;
        for (int i = 0; i < n; ++i)
        {
            ++leftCount[arr[i]];
            if (leftCount[arr[i]] > 1)
            {
                if (IsPer(arr, 0, i - 1) && IsPer(arr, i, n - 1))
                    answer.insert({i, n - i});
                break;
            }
        }

        for (int i = n - 1; i >= 0; --i)
        {
            ++rightCount[arr[i]];
            if (rightCount[arr[i]] > 1)
            {
                if (IsPer(arr, 0, i) && IsPer(arr, i + 1, n - 1))
                    answer.insert({i + 1, n - i - 1});
                break;
            }
        }

        printf("%u\n", answer.size());
        for (auto p : answer)
        {
            printf("%d %d\n", p.first, p.second);
        }
    }

    return 0;
}