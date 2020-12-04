#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

char map[2000][2001];
std::vector<int> xAxis[2000][10];
std::vector<int> yAxis[2000][10];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%s", map[i]);
        
        for (int r = 0; r < n; ++r)
        {
            for (int c = 0; c < n; ++c)
            {
                xAxis[c][map[r][c] - '0'].push_back(r);
                yAxis[r][map[r][c] - '0'].push_back(c);
            }
        }
        
        for (char ch = '0'; ch <= '9'; ++ch)
        {
            int maxArea = 0;
            // for (int r = 0; r < n; ++r)
            // {
            //     bool found = false;
            //     int minCol = n, maxCol = -1;
            //     for (int c = 0; c < n; ++c)
            //     {
            //         if (map[r][c] == ch)
            //         {
            //             found = true;
            //             minCol = std::min(minCol, c);
            //             maxCol = std::max(maxCol, c);
            //         }
            //     }

            //     if (found)
            //     {
            //         int area = (maxCol - minCol) * std::max(n - r - 1, r);
            //         maxArea = std::max(maxArea, area);
            //     }
            // }

            // for (int c = 0; c < n; ++c)
            // {
            //     bool found = false;
            //     int minRow = n, maxRow = -1;
            //     for (int r = 0; r < n; ++r)
            //     {
            //         if (map[r][c] == ch)
            //         {
            //             found = true;
            //             minRow = std::min(minRow, r);
            //             maxRow = std::max(maxRow, r);
            //         }
            //     }

            //     if (found)
            //     {
            //         int area = (maxRow - minRow) * std::max(n - c - 1, c);
            //         maxArea = std::max(maxArea, area);
            //     }
            // }

            for (int x = 0; x < n; ++x)
            {
                for (int y = 0; y < n; ++y)
                {
                    if (!xAxis[x][ch-'0'].empty() && !yAxis[y][ch-'0'].empty())
                    {
                        int minX = yAxis[y][ch-'0'][0];
                        int maxX = yAxis[y][ch-'0'].back();
                        int minY = xAxis[x][ch-'0'][0];
                        int maxY = xAxis[x][ch-'0'].back();

                        maxArea = std::max(maxArea, (maxX-minX) * (std::max(n-y-1, y)));
                        maxArea = std::max(maxArea, (maxY-minY) * (std::max(n-x-1, x)));
                        
                        maxArea = std::max(maxArea, (x-minX) * (n-minY-1));
                        maxArea = std::max(maxArea, (y-minY) * (n-minX-1));
                        maxArea = std::max(maxArea, (x-minX) * minY);
                        maxArea = std::max(maxArea, (y-minY) * minX);
                        maxArea = std::max(maxArea, abs(x-minX) * abs(y-minY));

                        maxArea = std::max(maxArea, (x-maxX) * (n-minY-1));
                        maxArea = std::max(maxArea, (y-minY) * (n-maxX-1));
                        maxArea = std::max(maxArea, (x-maxX) * minY);
                        maxArea = std::max(maxArea, (y-minY) * maxX);
                        maxArea = std::max(maxArea, abs(x-minX) * abs(y-maxY));

                        maxArea = std::max(maxArea, (x-minX) * (n-maxY-1));
                        maxArea = std::max(maxArea, (y-maxY) * (n-minX-1));
                        maxArea = std::max(maxArea, (x-minX) * maxY);
                        maxArea = std::max(maxArea, (y-maxY) * minX);
                        maxArea = std::max(maxArea, abs(x-maxX) * abs(y-maxY));

                        maxArea = std::max(maxArea, (x-maxX) * (n-maxY-1));
                        maxArea = std::max(maxArea, (y-maxY) * (n-maxX-1));
                        maxArea = std::max(maxArea, (x-maxX) * maxY);
                        maxArea = std::max(maxArea, (y-maxY) * maxX);
                        maxArea = std::max(maxArea, abs(x-maxX) * abs(y-minY));
                    }
                }
            }

            printf("%d ", maxArea);
        }
        printf("\n");

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                xAxis[i][j].clear();
                yAxis[i][j].clear();
            }
        }
    }

    return 0;
}