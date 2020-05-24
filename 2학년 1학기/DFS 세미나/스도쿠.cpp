#include <iostream>
#include <vector>

char board[9][10];
std::vector<std::pair<int, int>> toFill;
bool appearedInRow[9][9];
bool appearedInCol[9][9];
bool appearedInSub[9][9];

bool FillAll(int index)
{
    if (index >= (int)toFill.size())
        return true;

    std::pair<int, int>& point = toFill[index];
    int& row = point.first;
    int& col = point.second;
    char& current = board[row][col];

    int subIndex = (row / 3) * 3 + (col / 3);

    for (current = '1'; current <= '9'; ++current)
    {
        if (appearedInRow[row][current - '1'] || 
            appearedInCol[col][current - '1'] ||
            appearedInSub[subIndex][current - '1'])
            continue;
        
        appearedInRow[row][current - '1'] = true;
        appearedInCol[col][current - '1'] = true;
        appearedInSub[subIndex][current - '1'] = true;

        if (FillAll(index + 1))
            return true;
        
        appearedInRow[row][current - '1'] = false;
        appearedInCol[col][current - '1'] = false;
        appearedInSub[subIndex][current - '1'] = false;
    }

    current = '0';
    return false;
}

int main()
{
    for (int r = 0; r < 9; ++r)
    {
        scanf("%s", board[r]);
        for (int c = 0; c < 9; ++c)
        {
            if (board[r][c] == '0')
                toFill.push_back({r, c});
            else
            {
                int subIndex = (r / 3) * 3 + (c / 3);
                appearedInRow[r][board[r][c] - '1'] = true;
                appearedInCol[c][board[r][c] - '1'] = true;
                appearedInSub[subIndex][board[r][c] - '1'] = true;
            }
        }
    }

    FillAll(0);

    for (int r = 0; r < 9; ++r)
        printf("%s\n", board[r]);

    return 0;
}