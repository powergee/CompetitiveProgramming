#include <iostream>
#include <algorithm>
#include <queue>

int arr[2][1000000];

int mod;
bool compare(const int v1, const int v2)
{
    return v1 % mod < v2 % mod;
}

void radixSort(int nums[], int length, int e)
{
    static std::queue<int> buckets[2];

    for (int i = 0; i < length; ++i)
    {
        if (nums[i] & (1 << e))
            buckets[1].push(nums[i]);
        else
            buckets[0].push(nums[i]);
    }

    int index = 0;
    for (std::queue<int> &bucket : buckets)
    {
        while (!bucket.empty())
        {
            nums[index++] = bucket.front();
            bucket.pop();
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[0][i]);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[1][i]);

    long long first = 0, second = 0;
    
    for (int e = 0; e <= 28; ++e)
    {
        int digit = 1 << e;
        long long count[2] = {0, 0};

        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < n; ++j)
                if (arr[i][j] & digit)
                    ++count[i];
        
        first += digit * count[0] * count[1];
    }
    first %= 1999;

    std::queue<int> buckets[2];
    for (int e = 0; e <= 29; ++e)
    {
        radixSort(arr[0], n, e);
        radixSort(arr[1], n, e);

        int left = n, right = n, start = n;

        bool accepted = true;
        for (int i = 0; i < n && accepted; ++i)
        {
            while (left != 0 && (1 << e) - (arr[0][i] % (1 << e + 1)) <= (arr[1][left - 1] % (1 << e + 1)))
                --left;
            while (left < right && (arr[1][right - 1] % (1 << e + 1)) < (1 << (e + 1)) - (arr[0][i] % (1 << e + 1)))
                --right;
            while (start != 0 && (1 << e) - (arr[0][i] % (1 << e + 1)) <= (arr[1][start - 1] % (1 << e + 1)))
                --start;
            
            if (left != 0 || right != start)
                accepted = false;
        }

        if (accepted)
            second += (1<<e);
    }

    printf("%lld %lld", first, second);

    return 0;
}