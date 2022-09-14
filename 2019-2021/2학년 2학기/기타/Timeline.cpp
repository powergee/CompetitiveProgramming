#include <iostream>
#include <vector>
#include <algorithm>

int n, m, c;
int s[100001];
std::vector<std::pair<int, int>> prereqs[100001];
int answers[100001];

int getAnswer(int session)
{
    int& result = answers[session];
    if (result != -1)
        return result;
    
    result = s[session];
    for (auto pre : prereqs[session])
        result = std::max(result, getAnswer(pre.first)+pre.second);
    
    return result;
}

int main()
{
    scanf("%d %d %d", &n, &m, &c);

    for (int i = 1; i <= n; ++i)
        scanf("%d", s+i);
    
    for (int i = 1; i <= c; ++i)
    {
        int a, b;
        int x;
        scanf("%d %d %d", &a, &b, &x);
        prereqs[b].emplace_back(a, x);
    }

    std::fill(answers, answers+n+1, -1);

    for (int i = 1; i <= n; ++i)
        printf("%d\n", getAnswer(i));

    return 0;
}