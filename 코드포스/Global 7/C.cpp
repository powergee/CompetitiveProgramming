#define MOD 998244353
#include <iostream>
#include <algorithm>
#include <functional>

std::pair<int, int> arr[200000];
int pivot[200000];

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
    {
        int p;
        scanf("%d", &p);
        arr[i] = {p, i};
    }

    std::sort(arr, arr + n, std::greater<std::pair<int, int>>());
    
    long long pVal = 0;
    for (int i = 0; i < k; ++i)
    {
        pivot[i] = arr[i].second;
        pVal += arr[i].first;
    }
    std::sort(pivot, pivot + k);

    long long count = 1;

    for (int i = 0; i < k - 1; ++i)
    {
        count *= pivot[i + 1] - pivot[i];
        count %= MOD;
    }

    std::cout << pVal << ' ' << count << '\n';

    return 0;
}