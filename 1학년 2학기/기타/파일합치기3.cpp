#include <iostream>
#include <queue>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int K;
        std::priority_queue<long long> q;
        scanf("%d", &K);

        for (int i = 0; i < K; ++i)
        {
            long long size;
            scanf("%lld", &size);
            q.push(-size);
        }

        unsigned long long cost = 0;

        while (q.size() > 1)
        {
            long long a, b;
            a = q.top();
            q.pop();
            b = q.top();
            q.pop();
            q.push(a+b);
            cost += -(a+b);
        }

        if (T == 0)
            printf("%llu", cost);
        else
            printf("%llu\n", cost);
    }
}