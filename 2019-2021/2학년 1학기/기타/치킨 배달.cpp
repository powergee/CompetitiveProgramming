#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> Point;

int map[50][50];
std::vector<Point> house;
std::vector<Point> chicken;
int n, m;

int Dist(Point& p1, Point& p2)
{
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main()
{
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%d", &map[i][j]);

            if (map[i][j] == 1)
                house.emplace_back(i, j);
            else if (map[i][j] == 2)
                chicken.emplace_back(i, j);
        }
    }

    std::vector<bool> select(chicken.size(), false);
    std::fill(select.end() - m, select.end(), true);

    int minSum = 1e9;
    do {
        int sum = 0;
        
        for (unsigned i = 0; i < house.size(); ++i)
        {
            int minDist = 1e9;

            for (unsigned j = 0; j < chicken.size(); ++j)
            {
                if (!select[j])
                    continue;
                minDist = std::min(minDist, Dist(house[i], chicken[j]));
            }

            sum += minDist;
        }

        minSum = std::min(sum, minSum);
    } while (std::next_permutation(select.begin(), select.end()));

    std::cout << minSum;

    return 0;
}