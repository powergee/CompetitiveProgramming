#include <queue>
#include <vector>

void radixSort(std::vector<int>& nums)
{
    std::queue<int> buckets[2];
    for (int e = 0; e <= 31; ++e)
    {
        for (int num : nums)
        {
            if (num & (1<<e))
                buckets[1].push(num);
            else
                buckets[0].push(num);
        }

        int index = 0;
        for (std::queue<int>& bucket : buckets)
        {
            while (!bucket.empty())
            {
                nums[index++] = bucket.front();
                bucket.pop();
            }
        }
    }
}

void radixSort(int nums[], int length)
{
    std::queue<int> buckets[2];
    for (int e = 0; e <= 31; ++e)
    {
        for (int i = 0; i < length; ++i)
        {
            if (nums[i] & (1<<e))
                buckets[1].push(nums[i]);
            else
                buckets[0].push(nums[i]);
        }

        int index = 0;
        for (std::queue<int>& bucket : buckets)
        {
            while (!bucket.empty())
            {
                nums[index++] = bucket.front();
                bucket.pop();
            }
        }
    }
}