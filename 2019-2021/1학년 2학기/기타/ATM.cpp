#include <iostream>
#include <algorithm>

int nums[1000];

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &nums[i]);
    }

    std::sort(nums, nums + N);

    long long sum = 0;
    for (int i = 0 ; i < N; ++i)
    {
        sum += nums[i] * (N-i);
    }

    printf("%lld", sum);
}