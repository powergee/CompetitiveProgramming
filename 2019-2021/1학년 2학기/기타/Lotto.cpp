#include <iostream>
#include <algorithm>

int nums[12];
int toPrint[12];
int k;

void PrintArray(int* arr, int start, int last)
{
    if (start <= last)
    {
        for (int i = start; i < last; ++i)
        {
            printf("%d ", arr[i]);
        }
        printf("%d", arr[last]);
    }
}

void PrintAll(int pos, int numsBegin)
{
    if (pos + (k - numsBegin) == 6)
    {
        PrintArray(toPrint, 0, pos - 1);
        printf(" ");
        PrintArray(nums, numsBegin, k - 1);
        printf("\n");
    }
    else if (pos + (k - numsBegin) < 6)
        return;
    else if (pos == 6)
    {
        PrintArray(toPrint, 0, 5);
        printf("\n");
    }
    else
    {
        for (int i = 0; i <= k-6; ++i)
        {
            toPrint[pos] = nums[numsBegin + i];
            PrintAll(pos + 1, numsBegin + 1 + i);
        }
    }
}

int main()
{
    while (true)
    {
        scanf("%d", &k);

        if (k == 0)
        {
            break;
        }
        else
        {
            for (int i = 0; i < k; ++i)
            {
                scanf("%d", &nums[i]);
            }

            PrintAll(0, 0);
        }
        printf("\n");
    }
}