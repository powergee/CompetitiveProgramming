#include <iostream>
#include <string>
#include <queue>
#include <tuple>

bool map[10][10];
bool visited[10][10];

bool IsValid(int index)
{
    return 0 <= index && index < 10;
}

int main()
{
    std::pair<int, int> barn, lake;
    for (int row = 0; row < 10; ++row)
    {
        std::string line;
        std::cin >> line;
        
        for (int col = 0; col < 10; ++col)
        {
            switch (line[col])
            {
            case '.':
                map[row][col] = true;
                break;
            case 'B':
                map[row][col] = true;
                barn = {row, col};
                break;
            case 'R':
                map[row][col] = false;
                break;
            case 'L':
                lake = {row, col};
                break;
            }
        }
    }

    int result = 0;
    std::queue<std::tuple<int, int, int>> q;

    int row = lake.first, col = lake.second, dist = 0;

    if (IsValid(row - 1) && map[row - 1][col])
        q.push(std::make_tuple(row - 1, col, 0));

    if (IsValid(col - 1) && map[row][col - 1])
        q.push(std::make_tuple(row, col - 1, 0));

    if (IsValid(row + 1) && map[row + 1][col])
        q.push(std::make_tuple(row + 1, col, 0));
        
    if (IsValid(col + 1) && map[row][col + 1])
        q.push(std::make_tuple(row, col + 1, 0));

    while (!q.empty())
    {
        std::tie(row, col, dist) = q.front();
        q.pop();

        if (visited[row][col])
            continue;

        visited[row][col] = true;

        if (row == barn.first && col == barn.second)
        {
            result = dist;
            break;
        }

        if (IsValid(row - 1) && map[row - 1][col] && !visited[row - 1][col])
            q.push(std::make_tuple(row - 1, col, dist + 1));

        if (IsValid(col - 1) && map[row][col - 1] && !visited[row][col - 1])
            q.push(std::make_tuple(row, col - 1, dist + 1));

        if (IsValid(row + 1) && map[row + 1][col] && !visited[row + 1][col])
            q.push(std::make_tuple(row + 1, col, dist + 1));
            
        if (IsValid(col + 1) && map[row][col + 1] && !visited[row][col + 1])
            q.push(std::make_tuple(row, col + 1, dist + 1));
    }

    printf("%d", result);

    return 0;
}