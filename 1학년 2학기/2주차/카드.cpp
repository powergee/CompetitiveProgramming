#include <iostream>
#include <queue>

int main()
{
    int N;
    scanf("%d", &N);
    std::queue<int> q;
    for (int i = 1; i <= N; ++i)
        q.push(i);

    while (q.size() != 1)
    {
        q.pop();
        q.push(q.front());
        q.pop();
    }

    printf("%d", q.front());

    return 0;
}