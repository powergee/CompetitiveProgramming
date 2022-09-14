#include <iostream>
#include <algorithm>
using namespace std;

typedef long long Long;

int N, M, K;

Long memo[101][101][101];

Long Process(int rows, int cols, int rookCount)
{
    if (rookCount == 0 && !(rows < 0 || cols < 0))
        return 1;

    if (rookCount < 0)
        return 0;

    if (rows <= 0 || cols <= 0)
        return 0;

    if (rows == 1)
    {
        if (rookCount == 1)
            return cols;
        if (rookCount == 2)
            return cols * (cols - 1) / 2;
        else return 0;
    }

    if (cols == 1)
    {
        if (rookCount == 1)
            return rows;
        if (rookCount == 2)
            return rows * (rows - 1) / 2;
        else return 0;
    }
    
    Long& sum = memo[rows][cols][rookCount];
    if (sum != -1)
        return sum;
    sum = 0;

    // 가장 왼쪽 열에 안두는 경우
    sum += Process(rows, cols - 1, rookCount);
    // 가장 왼쪽 열에 1개 두는 경우
    sum += rows * (Process(rows - 1, cols - 1, rookCount - 1) + Process(rows - 1, cols - 2, rookCount - 2) * (cols - 1));
    sum %= 1000001;
    // 가장 왼쪽 열에 2개 두는 경우
    sum += Process(rows - 2, cols - 1, rookCount - 2) * (rows * (rows - 1) / 2);
    sum %= 1000001;

    return sum;
}

int main()
{
    scanf("%d %d %d", &N, &M, &K);
    fill(&memo[0][0][0], &memo[0][0][0] + sizeof(memo) / sizeof(Long), -1);
    printf("%ld", Process(N, M, K));
    return 0;
}