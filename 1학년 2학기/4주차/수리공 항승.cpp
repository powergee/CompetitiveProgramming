#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

std::vector<int> cracks;

int main()
{
    int n, l;
    scanf("%d %d", &n, &l);

    for (int i = 0; i < n; ++i)
    {
        int input;
        scanf("%d", &input);

        cracks.push_back(input);
    }

    std::sort(cracks.begin(), cracks.end());

    std::queue<int> q;
    for (int ele : cracks)
        q.push(ele);

    int coverage = q.front() + l - 1;
    int tapes = 1;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();

        if (coverage >= now)
        {
            continue;
        }
        else
        {
            coverage = now + l - 1;
            ++tapes;
        }
    }

    printf("%d", tapes);
}