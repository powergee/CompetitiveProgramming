#include <iostream>
#include <string>
#include <algorithm>

std::string map[50];
int n, m;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m;

    for (int i = 0; i < n; ++i)
        std::cin >> map[i];

    int maxRadius = 0;

    for (int r = 0; r < n; ++r)
    {
        for (int c = 0; c < m; ++c)
        {
            for (int radius = std::min(n - r, m - c); radius >= 1; --radius)
            {
                if (map[r][c] == map[r + radius - 1][c] &&
                    map[r + radius - 1][c] == map[r + radius - 1][c + radius - 1] &&
                    map[r + radius - 1][c + radius - 1] == map[r][c + radius - 1])
                    maxRadius = std::max(maxRadius, radius);
            }
        }
    }

    std::cout << maxRadius * maxRadius;

    return 0;
}