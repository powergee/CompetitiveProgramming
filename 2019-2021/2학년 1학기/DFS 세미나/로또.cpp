#include <iostream>
#include <algorithm>

int nums[12];
int toPrint[6];
int k;

void PrintAll(int pos, int numsBegin)
{
    if (pos + (k - numsBegin) < 6)
        return;

    else if (pos == 6)
    {
        for (int i = 0; i < 6; ++i)
            printf("%d ", toPrint[i]);
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
            break;

        if (k > 0)
        {
            for (int i = 0; i < k; ++i)
                scanf("%d", &nums[i]);

            PrintAll(0, 0);
        }
        printf("\n");
    }
}