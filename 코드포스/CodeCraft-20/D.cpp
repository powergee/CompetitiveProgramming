#include <iostream>
#include <algorithm>

std::pair<int, int> alice[1000][1000];
char map[1000][1000];
int n;

int exX = 0, exY = 0;
bool AbleToGo(int row, int col)
{
    return 0 <= row && row < n && 0 <= col && col < n && alice[row][col].first == exX && alice[row][col].second == exY;
}

void LoopDFS(int row, int col, char bf)
{
    if (AbleToGo(row + 1, col) && (map[row + 1][col] == 0 || map[row + 1][col] == 'X'))
    {
        LoopDFS(row + 1, col, 'U');
        if (bf == 0)
            map[row][col] = 'D';
    }

    if (AbleToGo(row, col + 1) && (map[row][col + 1] == 0 || map[row + 1][col] == 'X'))
    {
        LoopDFS(row, col + 1, 'L');
        if (bf == 0)
            map[row][col] = 'R';
    }

    if (AbleToGo(row - 1, col) && map[row - 1][col] != 0)
    {
        LoopDFS(row - 1, col, 'D');
        if (bf == 0)
            map[row][col] = 'U';
    }

    if (AbleToGo(row, col - 1) && map[row][col - 1] != 0)
    {
        LoopDFS(row, col - 1, 'R');
        if (bf == 0)
            map[row][col] = 'L';
    }

    if (bf != 0)
        map[row][col] = bf;
}

bool CellDFS(int row, int col)
{
    if (row + 1 == exX && col + 1 == exY)
    {
        map[row][col] = 'X';
        return true;
    }

    if (AbleToGo(row + 1, col) && map[row + 1][col] != 0)
    {
        if (CellDFS(row + 1, col))
        {
            map[row][col] = 'D';
            return true;
        }
    }

    if (AbleToGo(row, col + 1) && map[row][col + 1] != 0)
    {
        if (CellDFS(row, col + 1))
        {
            map[row][col] = 'R';
            return true;
        }
    }

    if (AbleToGo(row - 1, col) && map[row - 1][col] != 0)
    {
        if (CellDFS(row - 1, col))
        {
            map[row][col] = 'U';
            return true;
        }
    }

    if (AbleToGo(row, col - 1) && map[row][col - 1] != 0)
    {
        if (CellDFS(row, col - 1))
        {
            map[row][col] = 'L';
            return true;
        }
    }

    return false;
}

bool HandleLoop(int row, int col)
{
    exX = exY = -1;
    LoopDFS(row, col, 0);

    if (map[row][col] == 0)
        return false;
    return true;
}

bool HandleCell(int row, int col)
{
    exX = alice[row][col].first;
    exY = alice[row][col].second;

    return CellDFS(row, col);
}

int main()
{
    scanf("%d", &n);

    for (int row = 0; row < n; ++row)
        for (int col = 0; col < n; ++col)
            scanf("%d %d", &alice[row][col].first, &alice[row][col].second);

    bool valid = true;
    std::fill(&map[0][0], &map[0][0] + sizeof(map) / sizeof(char), 0);
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            if (map[row][col] != 0)
                continue;

            if (alice[row][col].first == -1)
            {
                if (!HandleLoop(row, col))
                {
                    valid = false;
                    goto EXIT;
                }
            }
            else
            {
                if (!HandleCell(row, col))
                {
                    valid = false;
                    goto EXIT;
                }
            }
        }
    } EXIT:

    if (valid)
    {
        printf("VALID\n");
        for (int row = 0; row < n; ++row)
        {
            for (int col = 0; col < n; ++col)
                printf("%c", map[row][col]);
            printf("\n");
        }
    }
    else printf("INVALID");

    return 0;
}