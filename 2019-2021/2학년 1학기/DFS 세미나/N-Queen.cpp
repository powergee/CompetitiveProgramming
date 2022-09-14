#include <iostream>
#include <algorithm>

int n;
int posCol[14];

bool CanAttack(int row)
{
    for (int i = 0; i < row; ++i)
        if (posCol[i] == posCol[row] || abs(i-row) == abs(posCol[i]-posCol[row]))
            return true;

    return false;
}

int PlaceQueen(int row)
{
    if (row >= n)
        return 1;
    
    int result = 0;
    for (int i = 0; i < n; ++i)
    {
        posCol[row] = i;
        if (!CanAttack(row))
            result += PlaceQueen(row + 1);
    }

    return result;
}

int main()
{
    scanf("%d", &n);
    printf("%d", PlaceQueen(0));
    return 0;
}