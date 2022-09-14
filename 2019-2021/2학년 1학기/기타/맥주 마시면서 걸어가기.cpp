#include <iostream>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> Point;

std::vector<Point> pos;
bool visited[102];
Point fes;

int GetDist(const Point& p1, const Point& p2)
{
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

bool DFS(int start)
{
    if (pos[start] == fes)
        return true;

    visited[start] = true;

    for (int i = (int)pos.size() - 1; i >= 0; --i)
        if (!visited[i] && GetDist(pos[start], pos[i]) <= 1000)
            if (DFS(i))
                return true;
    
    return false;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n + 2; ++i)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            pos.emplace_back(x, y);
        }

        fes = pos.back();

        if (DFS(0))
            printf("happy\n");
        else
            printf("sad\n");

        std::fill(visited, visited + n + 2, false);
        pos.clear();
    }

    return 0;
}