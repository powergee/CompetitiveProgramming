#include <iostream>
#include <algorithm>
#include <cmath>

typedef long long Long;

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

Long arr[100000];
Query qArr[100000];
Long answer[100000];


int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i); // 인덱스 0부터 초기화
    sqrtN = sqrt(n);

    for (int i = 0; i < m; ++i)
    {
        int left, right;
        scanf("%d %d", &left, &right);
        qArr[i] = {left - 1, right, i}; // [l-1, r) 구간 쿼리
    }
    std::sort(qArr, qArr + m);

    Long sum = 0;
    int start = qArr[0].start, end = qArr[0].end;
    for (int i = start; i < end; ++i)
        sum += arr[i];
    answer[qArr[0].index] = sum;

    for (int i = 1; i < m; ++i)
    {
        while (qArr[i].start < start)
            sum += arr[--start];
        while (end < qArr[i].end)
            sum += arr[end++];

        while (start < qArr[i].start)
            sum -= arr[start++];
        while (qArr[i].end < end)
            sum -= arr[--end];
        
        answer[qArr[i].index] = sum;
    }

    for (int i = 0; i < m; ++i)
        printf("%lld\n", answer[i]);

    return 0;
}