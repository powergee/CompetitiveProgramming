#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;
std::vector<int> trees;

Long getLength(int height)
{
    Long sum = 0;
    for (int tree : trees)
        if (tree > height)
            sum += tree - height;
    return sum;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    trees.resize(n);

    int maxHeight = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &trees[i]);
        maxHeight = std::max(maxHeight, trees[i]);
    }
    
    int left = 0, right = maxHeight;
    while (left+1 < right)
    {
        int mid = (left + right) / 2;
        
        if (getLength(mid) >= m)
            left = mid;
        else
            right = mid;
    }

    printf("%d", left);

    return 0;
}