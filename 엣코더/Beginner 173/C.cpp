#include <iostream>
#include <algorithm>
#include <vector>

int h, w, k;
char grid[6][7];

int countCases(int rCount, int cCount)
{
    int result = 0;

    std::vector<bool> rowCh(h);
    std::fill(rowCh.begin(), rowCh.end(), false);
    std::fill(rowCh.end() - rCount, rowCh.end(), true);

    do
    {
        std::vector<bool> colCh(w);
        std::fill(colCh.begin(), colCh.end(), false);
        std::fill(colCh.end() - cCount, colCh.end(), true);

        do
        {
            int black = 0;
            for (int i = 0; i < h; ++i)
                for (int j = 0; j < w; ++j)
                    if (!rowCh[i] && !colCh[j] && grid[i][j] == '#')
                        ++black;
            if (black == k)
                ++result;
        } while (std::next_permutation(colCh.begin(), colCh.end()));
    } while (std::next_permutation(rowCh.begin(), rowCh.end()));

    return result;
}

int main()
{
    scanf("%d %d %d", &h, &w, &k);

    for (int i = 0; i < h; ++i)
        scanf("%s", grid[i]);
    
    int black = 0, white = 0;
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (grid[i][j] == '.')
                ++white;
            else ++black;
        }
    }

    int result = 0;
    for (int rCount = 0; rCount < h; ++rCount)
        for (int cCount = 0; cCount < w; ++cCount)
            result += countCases(rCount, cCount);
    
    printf("%d", result);

    return 0;
}