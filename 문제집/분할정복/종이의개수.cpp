#include <iostream>
typedef std::pair<int, int> Point;

int paper[2187][2187];

void AddResult(Point start, Point end, int& minus, int& zero, int& one);

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            scanf("%d", &paper[i][j]);
        }
    }

    int minus = 0, zero = 0, one = 0;
    AddResult({0, 0}, {N-1, N-1}, minus, zero, one);

    printf("%d\n%d\n%d", minus, zero, one);

    return 0;
}

void AddResult(Point start, Point end, int& minus, int& zero, int& one)
{
    int sameNum = paper[start.first][end.second];

    for (int i = start.first; i <= end.first; ++i)
    {
        for (int j = start.second; j <= end.second; ++j)
        {
            if (sameNum != paper[i][j])
            {
                sameNum = -2;
                break;
            }
        }
    }

    if (sameNum == -2)
    {
        int length = (end.first - start.first + 1) / 3;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                Point newStart = {start.first + length * i, start.second + length * j};
                AddResult(newStart, {newStart.first + length - 1, newStart.second + length - 1}, minus, zero, one);
            }
        }
    }
    else
    {
        switch (sameNum)
        {
        case -1:
            ++minus;
            break;
        case 0:
            ++zero;
            break;
        case 1:
            ++one;
            break;
        }
    }
    
}

