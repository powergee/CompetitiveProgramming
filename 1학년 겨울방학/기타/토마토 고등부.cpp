#include <iostream>
#include <queue>

struct Point
{
    int X, Y, Z;
    Point(int x, int y, int z) : X(x), Y(y), Z(z) {}
    Point operator+(const Point& p)
    {
        return Point(X + p.X, Y + p.Y, Z + p.Z);
    }
};

const Point DIRS[]{ Point(1, 0, 0), Point(0, 1, 0), Point(0, 0, 1), Point(-1, 0, 0), Point(0, -1, 0), Point(0, 0, -1) };
int d1, d2, d3;
int box[1][1000][1000];
std::queue<std::pair<Point, int>> q;

bool IsValid(const Point& p)
{
    return (0 <= p.X && p.X < d1) && (0 <= p.Y && p.Y < d2) && (0 <= p.Z && p.Z < d3);
}

int& GetStatus(const Point& p)
{
    return box[p.X][p.Y][p.Z];
}

int main()
{
    scanf("%d %d", &d3, &d2);
    d1 = 1;

    for (int i = 0; i < d1; ++i)
        for (int j = 0; j < d2; ++j)
            for (int k = 0; k < d3; ++k)
                scanf("%d", &box[i][j][k]);

    for (int i = 0; i < d1; ++i)
    {
        for (int j = 0; j < d2; ++j)
        {
            for (int k = 0; k < d3; ++k)
            {
                if (box[i][j][k] == 1)
                {
                    Point now = Point(i, j, k);
                    for (int d = 0; d < 6; ++d)
                    {
                        Point next = now + DIRS[d];
                        if (IsValid(next) && GetStatus(next) == 0)
                            q.push({ next, 1 });
                    }
                }
            }
        }
    }

    int time = 0;
    while (!q.empty())
    {
        auto now = q.front();
        q.pop();

        if (GetStatus(now.first) == 1)
            continue;

        time = now.second;
        GetStatus(now.first) = 1;

        for (int i = 0; i < 6; ++i)
        {
            Point next = now.first + DIRS[i];
            if (IsValid(next) && GetStatus(next) == 0)
                q.push({ next, now.second + 1 });
        }
    }

    bool ripe = true;
    for (int i = 0; i < d1 && ripe; ++i)
        for (int j = 0; j < d2 && ripe; ++j)
            for (int k = 0; k < d3 && ripe; ++k)
                ripe = (box[i][j][k] != 0);

    printf("%d", (ripe ? time : -1));

    return 0;
}