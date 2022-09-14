#include <iostream>
#include <cmath>
#include <algorithm>

bool isSquare(int val)
{
    int sqrt = std::sqrt(val);
    return sqrt*sqrt == val;
}

int main()
{
    int n, m;
    int table[9][9];
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
    {
        char line[10];
        scanf("%s", line);
        for (int j = 0; j < m; ++j)
            table[i][j] = line[j] - '0';
    }

    int maxSquare = -1;
    for (int s = 0; s < n*m; ++s)
    {
        int sr = s / m, sc = s % m;
        if (isSquare(table[sr][sc]))
            maxSquare = std::max(maxSquare, table[sr][sc]);
        
        for (int e = 0; e < n*m; ++e)
        {
            if (s == e)
                continue;
            
            int er = e / m, ec = e % m;
            int dr = er - sr;
            int dc = ec - sc;
            char digits[10] = {0, };
            int dIndex = 0;

            for (int i = 0; ; ++i)
            {
                int cr = sr + i*dr;
                int cc = sc + i*dc;
                if (0 <= cr && cr < n && 0 <= cc && cc < m)
                {
                    digits[dIndex++] = char(table[cr][cc] + '0');
                    int combined = atoi(digits);
                    if (isSquare(combined))
                        maxSquare = std::max(maxSquare, combined);
                }
                else break;
            }
        }
    }

    printf("%d", maxSquare);

    return 0;
}