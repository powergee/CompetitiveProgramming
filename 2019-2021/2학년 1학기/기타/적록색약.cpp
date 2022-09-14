#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int n;
bool visited[100][100];
std::vector<std::string> map;

bool IsValid(int row, int col)
{
    return 0 <= row && row < n && 0 <= col && col < n;
}

int DFS(int row, int col)
{
    if (visited[row][col])
        return 0;
    
    visited[row][col] = true;

    int result = 1;
    if (IsValid(row - 1, col) && !visited[row - 1][col] && map[row - 1][col] == map[row][col])
        result += DFS(row - 1, col);
    if (IsValid(row + 1, col) && !visited[row + 1][col] && map[row + 1][col] == map[row][col])
        result += DFS(row + 1, col);
    if (IsValid(row, col + 1) && !visited[row][col + 1] && map[row][col + 1] == map[row][col])
        result += DFS(row, col + 1);
    if (IsValid(row, col - 1) && !visited[row][col - 1] && map[row][col - 1] == map[row][col])
        result += DFS(row, col - 1);

    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        std::string line;
        std::cin >> line;
        map.push_back(line);
    }

    int count[2] {0, 0};
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            count[0] += (DFS(i, j) > 0 ? 1 : 0);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (map[i][j] == 'R')
                map[i][j] = 'G';
    
    std::fill(&visited[0][0], &visited[0][0] + sizeof(visited) / sizeof(bool), false);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            count[1] += (DFS(i, j) > 0 ? 1 : 0);

    std::cout << count[0] << " " << count[1];

    return 0;
}