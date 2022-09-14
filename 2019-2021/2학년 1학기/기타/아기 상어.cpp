#include <iostream>
#include <queue>

typedef std::pair<int, int> Point;
typedef std::pair<int, Point> QEle;

struct QEleCompare
{
    bool operator()(const QEle& q1, const QEle& q2)
    {
        if (q1.first == q2.first)
        {
            if (q1.second.first == q2.second.first)
                return q1.second.second > q2.second.second;
            else return q1.second.first > q2.second.first;
        }
        else return q1.first > q2.first;
    }
};

int n;
int map[20][20];
int sSize = 2;

bool IsValid(int i, int j)
{
    return 0 <= i && i < n && 0 <= j && j < n;
}

Point FindPrey(const Point& start)
{
    std::priority_queue<QEle, std::vector<QEle>, QEleCompare> q;
    q.push({0, start});
    bool visited[20][20] = {0, };

    while (!q.empty())
    {
        QEle now = q.top();
        q.pop();

        int& dist = now.first;
        int& i = now.second.first;
        int& j = now.second.second;

        if (visited[i][j])
            continue;
        visited[i][j] = true;

        if (map[i][j] != 0 && map[i][j] < map[start.first][start.second])
            return {i, j};

        if (IsValid(i - 1, j) && !visited[i - 1][j] && map[i - 1][j] <= map[start.first][start.second])
            q.push({dist + 1, Point(i - 1, j)});
        if (IsValid(i + 1, j) && !visited[i + 1][j] && map[i + 1][j] <= map[start.first][start.second])
            q.push({dist + 1, Point(i + 1, j)});
        if (IsValid(i, j - 1) && !visited[i][j - 1] && map[i][j - 1] <= map[start.first][start.second])
            q.push({dist + 1, Point(i, j - 1)});
        if (IsValid(i, j + 1) && !visited[i][j + 1] && map[i][j + 1] <= map[start.first][start.second])
            q.push({dist + 1, Point(i, j + 1)});
    }

    return {-1, -1};
}

int GetDist(const Point& p1, const Point& p2)
{
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main()
{
    scanf("%d", &n);

    Point pos, preyPos;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%d", &map[i][j]);

            if (map[i][j] == 9)
            {
                pos = {i, j};
                map[i][j] = 0;
            }
        }
    }

    int time = 0;
    int count = 0;
    while ((preyPos = FindPrey(pos)).first != -1)
    {
        time += GetDist(preyPos, pos);
        pos = preyPos;
        ++count;

        if (count == sSize)
        {
            count = 0;
            ++sSize;
        }
    }

    printf("%d", time);

    return 0;
}