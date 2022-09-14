#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> requests;
int n, m;

bool isSatisfied(int bound)
{
    int sum = 0;
    for (int req : requests)
        sum += std::min(req, bound);
    return sum <= m;
}

int main()
{
    scanf("%d", &n);

    int maxRequest = 0;
    for (int i = 0; i < n; ++i)
    {
        int req;
        scanf("%d", &req);
        requests.push_back(req);
        maxRequest = std::max(maxRequest, req);
    }

    scanf("%d", &m);

    int left = 0, right = maxRequest + 1;
    while (left+1 < right)
    {
        int mid = (left + right) / 2;
        
        if (isSatisfied(mid))
            left = mid;
        else
            right = mid;
    }

    printf("%d", left);

    return 0;
}