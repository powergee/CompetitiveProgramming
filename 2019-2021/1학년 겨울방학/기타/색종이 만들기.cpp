#include <iostream>

bool paper[128][128];

int truePaper, falsePaper;

bool AllSame(int rStart, int rEnd, int cStart, int cEnd)
{
    bool pivot = paper[rStart][cStart];

    for (int row = rStart; row <= rEnd; ++row)
        for (int col = cStart; col <= cEnd; ++col)
            if (pivot != paper[row][col])
                return false;

    pivot ? ++truePaper : ++falsePaper;
    return true;
}

void Count(int rStart, int rEnd, int cStart, int cEnd)
{
    if (AllSame(rStart, rEnd, cStart, cEnd))
        return;
    
    int width = cEnd - cStart + 1;
    int height = rEnd - rStart + 1;

    Count(rStart, rStart + height / 2 - 1, cStart, cStart + width / 2 - 1);
    Count(rStart, rStart + height / 2 - 1, cStart + width / 2, cEnd);
    Count(rStart + height / 2, rEnd, cStart, cStart + width / 2 - 1);
    Count(rStart + height / 2, rEnd, cStart + width / 2, cEnd);
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            int input;
            scanf("%d", &input);
            paper[row][col] = input == 1 ? true : false;
        }
    }

    Count(0, n - 1, 0, n - 1);
    printf("%d\n%d", falsePaper, truePaper);

    return 0;
}