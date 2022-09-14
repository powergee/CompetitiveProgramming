#include <iostream>

int row, col;
char map[1000][1001];
bool visited[1000][1000];

bool Available(int r, int c)
{
    return 0 <= r && r < row && 0 <= c && c < col && !visited[r][c] && map[r][c] == '0';
}

bool FindInner(int r, int c)
{
    visited[r][c] = true;

    if (r == row - 1)
        return true;

    if (Available(r - 1, c))
        if (FindInner(r - 1, c))
            return true;

    if (Available(r + 1, c))
        if (FindInner(r + 1, c))
            return true;

    if (Available(r, c - 1))
        if (FindInner(r, c - 1))
            return true;

    if (Available(r, c + 1))
        if (FindInner(r, c + 1))
            return true;

    return false;
}

int main()
{
    scanf("%d %d", &row, &col);

    for (int r = 0; r < row; ++r)
        scanf("%s", map[r]);

    bool yes = false;
    for (int c = 0; c < col; ++c)
    {
        if (Available(0, c) && FindInner(0, c))
        {
            yes = true;
            break;
        }
    }

    if (yes)
        printf("YES");
    else printf("NO");

    return 0;
}