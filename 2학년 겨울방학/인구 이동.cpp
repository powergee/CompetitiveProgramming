#include <iostream>
#include <vector>
#include <algorithm>

int popul[50][50];
int parent[2500];
bool visited[50][50];
int n, l, r;

int find(int x)
{
    if (parent[x] == x)
        return x;
    
    return parent[x] = find(parent[x]);
}

void merge(int x, int y)
{
    int xPar = find(x);
    int yPar = find(y);

    if (xPar != yPar)
        parent[xPar] = yPar;
}

void DFS(int r, int c, std::vector<std::pair<int, int>>& nodes)
{
    visited[r][c] = true;
    nodes.emplace_back(r, c);

    if (0 <= r-1 && !visited[r-1][c] && find((r-1)*n+c) == find(r*n+c))
        DFS(r-1, c, nodes);
    if (r+1 < n && !visited[r+1][c] && find((r+1)*n+c) == find(r*n+c))
        DFS(r+1, c, nodes);
    if (0 <= c-1 && !visited[r][c-1] && find(r*n+c-1) == find(r*n+c))
        DFS(r, c-1, nodes);
    if (c+1 < n && !visited[r][c+1] && find(r*n+c+1) == find(r*n+c))
        DFS(r, c+1, nodes);
}

int main()
{
    scanf("%d %d %d", &n, &l, &r);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &popul[i][j]);

    int answer = 0;
    while (true)
    {
        std::fill(&visited[0][0], &visited[0][0] + sizeof(visited) / sizeof(bool), false);
        for (int i = 0; i < n*n; ++i)
            parent[i] = i;
        
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i+1 < n)
                {
                    int downDiff = abs(popul[i][j] - popul[i+1][j]);
                    if (l <= downDiff && downDiff <= r)
                        merge(i*n+j, (i+1)*n+j);
                }
                
                if (j+1 < n)
                {
                    int rightDiff = abs(popul[i][j] - popul[i][j+1]);
                    if (l <= rightDiff && rightDiff <= r)
                        merge(i*n+j, i*n+j+1);
                }
            }
        }

        std::vector<std::pair<int, int>> nodes;
        bool moved = false;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (!visited[i][j])
                {
                    DFS(i, j, nodes);
                    moved |= (nodes.size() > 1);
                    int sum = 0;
                    for (auto p : nodes)
                        sum += popul[p.first][p.second];
                    for (auto p : nodes)
                        popul[p.first][p.second] = (sum / (int)nodes.size());
                    nodes.clear();
                }
            }
        }

        if (!moved)
            break;
        else ++answer;
    }

    printf("%d", answer);

    return 0;
}