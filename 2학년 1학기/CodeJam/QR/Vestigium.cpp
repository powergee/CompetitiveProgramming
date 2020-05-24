#include <iostream>
#include <set>

bool IsLatinRow(int r, int n, int matrix[][100])
{
    std::set<int> vals;
    for (int c = 0; c < n; ++c)
    {
        if (vals.find(matrix[r][c]) == vals.end())
            vals.insert(matrix[r][c]);
        else return false;
    }
    return true;
}

bool IsLatinCol(int c, int n, int matrix[][100])
{
    std::set<int> vals;
    for (int r = 0; r < n; ++r)
    {
        if (vals.find(matrix[r][c]) == vals.end())
            vals.insert(matrix[r][c]);
        else return false;
    }
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);
    
    for (int c = 1; c <= T; ++c)
    {
        int n;
        int matrix[100][100];
        scanf("%d", &n);
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &matrix[i][j]);
        
        int trace = 0, rowCount = 0, colCount = 0;
        
        for (int i = 0; i < n; ++i)
        {
            trace += matrix[i][i];
            if (!IsLatinRow(i, n, matrix))
                ++rowCount;
            if (!IsLatinCol(i, n, matrix))
                ++colCount;
        }
        
        printf("Case #%d: %d %d %d\n", c, trace, rowCount, colCount);
    }
    
    return 0;
}