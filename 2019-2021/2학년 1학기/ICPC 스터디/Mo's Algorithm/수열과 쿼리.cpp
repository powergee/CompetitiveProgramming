#include <iostream>
#include <algorithm>
#include <cmath>

int sqrtN;
struct Query
{
    int start, end, index;
    
    bool operator<(const Query& q) const
    {
        if (start / sqrtN != q.start / sqrtN)
            return start / sqrtN < q.start / sqrtN;
        else return end < q.end;
    }
};

int arr[100000];
Query qArr[100000];
int answer[100000];
int count[1000001];

int main()
{
    int n, m;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i); // 인덱스 0부터 초기화
    sqrtN = sqrt(n);

    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
        int left, right;
        scanf("%d %d", &left, &right);
        qArr[i] = {left - 1, right, i}; // [l-1, r) 구간 쿼리
    }
    std::sort(qArr, qArr + m);

    int currCount = 0;
    int start = qArr[0].start, end = qArr[0].end;
    for (int i = start; i < end; ++i)
    {
        ++count[arr[i]];
        if (count[arr[i]] == 1)
            ++currCount;
    }
    answer[qArr[0].index] = currCount;

    for (int i = 1; i < m; ++i)
    {
        while (qArr[i].start < start)
        {
            ++count[arr[--start]];
            if (count[arr[start]] == 1)
                ++currCount;
        }

        while (end < qArr[i].end)
        {
            ++count[arr[end]];
            if (count[arr[end++]] == 1)
                ++currCount;
        }

        while (start < qArr[i].start)
        {
            --count[arr[start]];
            if (count[arr[start++]] == 0)
                --currCount;
        }

        while (qArr[i].end < end)
        {
            --count[arr[--end]];
            if (count[arr[end]] == 0)
                --currCount;
        }
        
        answer[qArr[i].index] = currCount;
    }

    for (int i = 0; i < m; ++i)
        printf("%d\n", answer[i]);

    return 0;
}