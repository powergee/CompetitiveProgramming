#include <iostream>

bool map[100][100];

int main()
{
    int n;
    scanf("%d", &n);

    while (n--)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        for (int row = y; row < y + 10; ++row)
            for (int col = x; col < x + 10; ++col)
                map[row][col] = true;
    }

    int area = 0;
    for (int row = 0; row < 100; ++row)
        for (int col = 0; col < 100; ++col)
            if (map[row][col])
                ++area;

    printf("%d", area);

    return 0;
}