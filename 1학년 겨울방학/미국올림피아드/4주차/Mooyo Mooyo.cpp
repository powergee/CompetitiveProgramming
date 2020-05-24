#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
typedef std::pair<int, int> Point;

std::vector<std::string> map;
std::set<Point> totalVisited;
std::set<Point> visited;
std::set<Point> toDelete;
int n, k;
int dfsVisited = 0;

bool IsVisited(const Point& p, const std::set<Point>& viSet)
{
    return !viSet.empty() && viSet.find(p) != viSet.end();
}

void DFS(Point start)
{
    if (IsVisited(start, visited))
        return;
    
    //std::cout << "{ " << start.first << ", " << start.second << " } -> ";
    visited.insert(start);
    ++dfsVisited;
    int& row = start.first;
    int& col = start.second;

    if (row - 1 >= 0 && map[row][col] == map[row - 1][col])
        DFS({ row - 1, col });
    if (row + 1 < n && map[row][col] == map[row + 1][col])
        DFS({ row + 1, col });
    if (col - 1 >= 0 && map[row][col] == map[row][col - 1])
        DFS({ row, col - 1 });
    if (col + 1 < 10 && map[row][col] == map[row][col + 1])
        DFS({ row, col + 1 });
}

bool FindRegions()
{
    bool found = false;
    visited.clear();

    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < 10; ++col)
        {
            if (map[row][col] == '0' || IsVisited({ row, col }, totalVisited))
                continue;

            dfsVisited = 0;
            //std::cout << "DFS: ";
            DFS({ row, col });
            //std::cout << "\n";

            //std::cout << "dfsVisited: " << dfsVisited << "\n";
            if (dfsVisited >= k)
            {
                found = true;
                toDelete.insert(visited.begin(), visited.end());
            }

            totalVisited.insert(visited.begin(), visited.end());
            visited.clear();
        }
    }

    return found;
}

void TrimCol(int col)
{
    std::queue<char> q;
    for (int row = n - 1; row >= 0; --row)
    {
        if (map[row][col] != '0')
        {
            q.push(map[row][col]);
            map[row][col] = '0';
        }
    }

    for (int row = n - 1; !q.empty(); --row)
    {
        map[row][col] = q.front();
        q.pop();
    }
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> k;

    for (int row = 0; row < n; ++row)
    {
        std::string line;
        std::cin >> line;
        map.push_back(line);
    }

    while (FindRegions())
    {
        for (auto del : toDelete)
            map[del.first][del.second] = '0';

        for (int col = 0; col < 10; ++col)
            TrimCol(col);

        totalVisited.clear();
        visited.clear();
        toDelete.clear();
    }

    for (std::string& line : map)
    {
        std::cout << line << "\n";
    }

    return 0;
}