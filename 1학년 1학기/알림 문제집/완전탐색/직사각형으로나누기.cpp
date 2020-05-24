#include <iostream>
#include <algorithm>
using namespace std;

int rows;
int cols;

int rowSum[100];
int colSum[100];

int table[100][100];

bool rowSelect[100];
bool colSelect[100];

//int colsSum_Memo[99][99];

int ColsSum(int start, int last)
{
    if ((last - start + 1) * rows < 3)
        return 0;

    int sum = 0;
    for (int i = start; i <= last; ++i)
    {
        sum += colSum[i];
    }

    return sum;
}

//int rowsSum_Memo[99][99];

int RowsSum(int start, int last)
{
    if ((last - start + 1) * cols < 3)
        return 0;

    int sum = 0;
    for (int i = start; i <= last; ++i)
    {
        sum += rowSum[i];
    }

    return sum;
}

int GetUpLeft(int height, int width)
{
    if ()
}

int GetDownLeft(int height, int width)
{

}

int GetUpRight(int height, int width)
{

}

int GetDownRight(int height, int width)
{

}

int main()
{
    //fill(&colsSum_Memo[0][0], &colsSum_Memo[0][0] + sizeof(colsSum_Memo) / sizeof(int), -1);

    cin >> rows >> cols;
    
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            char input;
            scanf("%c", &input);
            
            if (input < '0' || input > '9')
            {
                --c;
                continue;
            }

            table[r][c] = (int)(input - '0');

            rowSum[r] += table[r][c];
            colSum[c] += table[r][c];
        }
    }

    int result = -1;

    fill(colSelect, colSelect + 2, true);
    do
    {
        int a = -1, b = -1;

        for (int i = 0; i < cols - 1; ++i)
        {
            if (colSelect[i])
            {
                if (a == -1)
                    a = i;
                else b = i;
            }
        }

        max(result, ColsSum(0, a) * ColsSum(a+1, b) * ColsSum(b+1, cols-1));
    }while (next_permutation(colSelect, colSelect + cols - 1))

    fill(rowSelect, rowSelect + 2, true);
    do
    {
        int a = -1, b = -1;

        for (int i = 0; i < rows - 1; ++i)
        {
            if (rowSelect[i])
            {
                if (a == -1)
                    a = i;
                else b = i;
            }
        }

        max(result, RowsSum(0, a) * RowsSum(a+1, b) * RowsSum(b+1, rows-1));
    }while (next_permutation(rowSelect, rowSelect + rows - 1))



    return 0;
}