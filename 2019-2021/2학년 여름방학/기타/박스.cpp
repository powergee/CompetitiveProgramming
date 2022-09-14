#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int height, width;
        int table[100][100];
        scanf("%d %d", &height, &width);

        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                scanf("%d", &table[i][j]);
        
        int result = 0;
        for (int col = 0; col < width; ++col)
        {
            int blankCount = 0;
            for (int row = height - 1; row >= 0; --row)
            {
                if (table[row][col])
                    result += blankCount;
                else ++blankCount;
            }
        }

        printf("%d\n", result);
    }

    return 0;
}