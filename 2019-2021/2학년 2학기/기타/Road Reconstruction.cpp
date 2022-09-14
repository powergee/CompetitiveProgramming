#include <iostream>
#include <vector>
#include <queue>

struct DijkElement
{
    int row, col, cost;

    bool operator<(const DijkElement& e) const
    {
        return cost > e.cost;
    }
};

const std::pair<int, int> DIRS[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int map[1000][1000];
int dist[1000][1000];
int m, n;

int main()
{
    scanf("%d %d", &m, &n);

    for (int r = 0; r < m; ++r)
        for (int c = 0; c < n; ++c)
            scanf("%d", &map[r][c]);
    
    if (map[0][0] == -1)
        printf("-1");
    else 
    {
        for (int r = 0; r < m; ++r)
            for (int c = 0; c < n; ++c)
                dist[r][c] = 1e9;

        dist[0][0] = map[0][0];
        std::priority_queue<DijkElement> q;
        q.push({0, 0, dist[0][0]});

        while (!q.empty())
        {
            DijkElement now = q.top();
            q.pop();

            for (int i = 0; i < 4; ++i)
            {
                std::pair<int, int> next = {now.row + DIRS[i].first,
                                            now.col + DIRS[i].second};

                if (0 <= next.first && next.first < m && 
                    0 <= next.second && next.second < n && 
                    map[next.first][next.second] != -1)
                {
                    int newDist = dist[now.row][now.col] + map[next.first][next.second];
                    if (newDist < dist[next.first][next.second])
                    {
                        dist[next.first][next.second] = newDist;
                        q.push({next.first, next.second, newDist});
                    }
                }
            }
        }

        // for (int r = 0; r < m; ++r)
        // {
        //     for (int c = 0; c < n; ++c)
        //         printf("%d ", dist[r][c]);
        //     printf("\n");
        // }

        if (dist[m-1][n-1] == 1e9)
            printf("-1");
        else printf("%d", dist[m-1][n-1]);
    }

    return 0;
}