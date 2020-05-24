#include <iostream>
#include <algorithm>
 
int n;
int arr[200001];
int tree1[600001];
int tree2[600001];
int dp1[200001];
int dp2[200001];
std::pair<int, int> answer;
 
int InitMax(int treeIndex, int start, int end)
{
    if (start == end)
        return tree1[treeIndex] = arr[start];
 
    int r1 = InitMax(treeIndex * 2, start, (start + end) / 2);
    int r2 = InitMax(treeIndex * 2 + 1, (start + end) / 2 + 1, end);
 
    return tree1[treeIndex] = std::max(r1, r2);
}
 
int QueryMax(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
{
    int nodeMed = (nodeStart + nodeEnd) / 2;
 
    if (nodeStart > reqEnd || nodeEnd < reqStart)
        return -0x7fffffff;
 
    else if (nodeStart >= reqStart && nodeEnd <= reqEnd)
        return tree1[index];
 
    else
        return std::max(QueryMax(index * 2, nodeStart, nodeMed, reqStart, reqEnd), QueryMax(index * 2 + 1, nodeMed + 1, nodeEnd, reqStart, reqEnd));
}
 
int InitMin(int treeIndex, int start, int end)
{
    if (start == end)
        return tree2[treeIndex] = arr[start];
 
    int r1 = InitMin(treeIndex * 2, start, (start + end) / 2);
    int r2 = InitMin(treeIndex * 2 + 1, (start + end) / 2 + 1, end);
 
    return tree2[treeIndex] = std::min(r1, r2);
}
 
int QueryMin(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
{
    int nodeMed = (nodeStart + nodeEnd) / 2;
 
    if (nodeStart > reqEnd || nodeEnd < reqStart)
        return 0x7fffffff;
 
    else if (nodeStart >= reqStart && nodeEnd <= reqEnd)
        return tree2[index];
 
    else
        return std::min(QueryMin(index * 2, nodeStart, nodeMed, reqStart, reqEnd), QueryMin(index * 2 + 1, nodeMed + 1, nodeEnd, reqStart, reqEnd));
}
 
bool Find(int start, int last, int max, int min)
{
    if (last - start <= 0)
        return false;
 
    if ((max - min) >= (last - start + 1))
    {
        answer = {start, last};
        return true;
    }
    else
    {
        if (!dp1[start] && !dp2[last])
            return false;

        bool left = arr[start] == min || arr[start] == max;
        bool right = arr[last] == min || arr[last] == max;

        if (!left && !right)
        {
            if (Find(start + 1, last - 1, QueryMax(1, 1, n, start + 1, last - 1), QueryMin(1, 1, n, start + 1, last - 1)))
                return true;
        }

        else
        {
            if (!left)
            {
                if (Find(start + 1, last, QueryMax(1, 1, n, start + 1, last), QueryMin(1, 1, n, start + 1, last)))
                    return true;
            }
    
            else if (!right)
            {
                if (Find(start, last - 1, QueryMax(1, 1, n, start, last - 1), QueryMin(1, 1, n, start, last - 1)))
                    return true;
            }
        }
 
        if (Find(start + 1, last, QueryMax(1, 1, n, start + 1, last), QueryMin(1, 1, n, start + 1, last)))
            return true;
 
        if (Find(start, last - 1, QueryMax(1, 1, n, start, last - 1), QueryMin(1, 1, n, start, last - 1)))
            return true;
 
        dp1[start] = dp2[last] = 0;
    }
    
    return false;
}
 
int main()
{
    int T;
    scanf("%d", &T);
 
    while (T--)
    {
        scanf("%d", &n);

        int minPos = 1, maxPos = 1;
 
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", arr + i);

            if (arr[minPos] > arr[i])
                minPos = i;
            else if (arr[minPos] == arr[i] && minPos < maxPos)
                minPos = i;

            if (arr[maxPos] < arr[i])
                maxPos = i;
            else if (arr[maxPos] == arr[i] && maxPos < minPos)
                maxPos = i;
        }
 
        InitMax(1, 1, n);
        InitMin(1, 1, n);
 
        std::fill(dp1, dp1 + n + 1, 1);
        std::fill(dp2, dp2 + n + 1, 1);

        int start = std::min(minPos, maxPos);
        int last = std::max(maxPos, minPos);
 
        if (Find(start, last, QueryMax(1, 1, n, start, last), QueryMin(1, 1, n, start, last)))
            printf("YES\n%d %d\n", answer.first, answer.second);
        else printf("NO\n");
    }
}