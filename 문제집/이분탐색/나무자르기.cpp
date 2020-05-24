#include <iostream>
typedef long long Long;
int trees[1000000];

Long Cut(int height, int* treeArr, int treeCount);

int main()
{
    int treeCount, need;
    scanf("%d %d", &treeCount, &need);

    int left = 0, right = -1, pivot;

    for (int i = 0; i < treeCount; ++i)
    {
        scanf("%d", &trees[i]);

        if (trees[i] > right)
            right = trees[i];
    }

    Long sum = 0;
    pivot = (left + right) / 2;
    
    while (sum != need)
    {
        sum = Cut(pivot, trees, treeCount);

        if (sum > need)
        {
            left = pivot;
        }
        else if (sum < need)
        {
            right = pivot;
        }
        
        int newPivot = (left + right) / 2;
        if (pivot == newPivot && sum != need)
        {
            if (Cut(right, trees, treeCount) >= need)
                pivot = right;
            else pivot = left;

            break;
        }
        else pivot = newPivot;
    }

    printf("%d", pivot);

    return 0;
}

Long Cut(int height, int* treeArr, int treeCount)
{
    Long result = 0;

    for (int i = 0; i < treeCount; ++i)
    {
        int toAdd = treeArr[i] - height;
        result += toAdd < 0 ? 0 : toAdd;
    }

    return result;
}