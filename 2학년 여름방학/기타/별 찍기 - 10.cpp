#include <iostream>

char** result;

void fillResult(int x, int y, int width)
{
    if (width == 1)
    {
        result[x][y] = '*';
        return;
    }

    int unit = width/3;

    fillResult(x, y, unit);
    fillResult(x+unit, y, unit);
    fillResult(x+2*unit, y, unit);

    fillResult(x, y+unit, unit);
    fillResult(x+2*unit, y+unit, unit);
    
    fillResult(x, y+2*unit, unit);
    fillResult(x+unit, y+2*unit, unit);
    fillResult(x+2*unit, y+2*unit, unit);
}

int main()
{
    int n;
    scanf("%d", &n);
    result = new char*[n];
    for (int i = 0; i < n; ++i)
        result[i] = new char[n+1];
    
    fillResult(0, 0, n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            if (!result[i][j])
                result[i][j] = ' ';
        printf("%s\n", result[i]);
    }
}