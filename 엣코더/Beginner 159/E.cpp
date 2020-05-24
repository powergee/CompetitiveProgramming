#include <iostream>
#include <algorithm>
#include <vector>

char s[10][1001];
int h, w, k;

int CountWhiteInRow(int row, int cStart, int cEnd)
{
    int count = 0;
    for (int col = cStart; col <= cEnd; ++col)
        if (s[row][col] == '1')
            ++count;

    return count;
}

int CountWhiteInCol(int col, int rStart, int rEnd)
{
    int count = 0;
    for (int row = rStart; row <= rEnd; ++row)
        if (s[row][col] == '1')
            ++count;

    return count;
}

int TryToCut(int rStart, int rEnd, int cStart, int cEnd)
{
    std::vector<int> rCount, cCount;
    int whiteSum = 0;

    for (int i = rStart; i <= rEnd; ++i)
    {
        rCount.push_back(CountWhiteInRow(i, cStart, cEnd));
        whiteSum += rCount.back();
    }

    if (whiteSum <= k)
        return 0;
    
    for (int i = cStart; i <= cEnd; ++i)
        cCount.push_back(CountWhiteInCol(i, rStart, rEnd));

    std::vector<int> rLeft, rRight, cLeft, cRight;

    rLeft.push_back(rCount[0]);
    for (int i = rStart + 1; i <= rEnd; ++i)
        rLeft.push_back(rLeft.back() + rCount[i - rStart]);
    
    rRight.push_back(rLeft.back());
    for (int i = 1; i < rEnd - rStart + 1; ++i)
        rRight.push_back(rLeft.back() - rLeft[i - 1]);

    cLeft.push_back(cCount[0]);
    for (int i = cStart + 1; i <= cEnd; ++i)
        cLeft.push_back(cLeft.back() + cCount[i - cStart]);
    
    cRight.push_back(cLeft.back());
    for (int i = 1; i < cEnd - cStart + 1; ++i)
        cRight.push_back(cLeft.back() - cLeft[i - 1]);

    /*for (int count : rLeft)
        printf("%d ", count);
    printf("\n");

    for (int count : rRight)
        printf("%d ", count);
    printf("\n");

    for (int count : cLeft)
        printf("%d ", count);
    printf("\n");

    for (int count : cRight)
        printf("%d ", count);
    printf("\n");*/

    int diff = 1e9;
    std::pair<int, char> cut = {-1, 0};

    for (unsigned r = 0; r < rCount.size() - 1; ++r)
    {
        int currDiff = abs(rLeft[r] - rRight[r + 1]);
        if (diff > currDiff)
        {
            diff = currDiff;
            cut = {r, 'r'};
        }
    }

    for (unsigned c = 0; c < cCount.size() - 1; ++c)
    {
        int currDiff = abs(cLeft[c] - cRight[c + 1]);
        if (diff > currDiff)
        {
            diff = currDiff;
            cut = {c, 'c'};
        }
    }

    if (cut.second == 'r')
        return 1 + TryToCut(rStart, cut.first, cStart, cEnd) + TryToCut(cut.first + 1, rEnd, cStart, cEnd);
    else return 1 + TryToCut(rStart, rEnd, cStart, cut.first) + TryToCut(rStart, rEnd, cut.first + 1, cEnd);
}

int main()
{
    scanf("%d %d %d", &h, &w, &k);

    for (int row = 0; row < h; ++row)
        scanf("%s", s[row]);
    
    printf("%d", TryToCut(0, h - 1, 0, w - 1));

    return 0;
}