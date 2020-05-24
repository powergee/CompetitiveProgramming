#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#define MAXINPUT 10000

int n, m;
std::vector<int> graph[MAXINPUT * 2];
std::vector<int> reverse[MAXINPUT * 2];
bool visited1[MAXINPUT * 2];
bool visited2[MAXINPUT * 2];
int belong[MAXINPUT * 2];

int Not(int pos)
{
    return (pos < MAXINPUT ? pos + MAXINPUT : pos - MAXINPUT);
}

void FirstDFS(int start, std::stack<int>& s)
{
    if (visited1[start])
        return;

    visited1[start] = true;

    for (int next : graph[start])
        FirstDFS(next, s);

    s.push(start);
}

void SecondDFS(int start, int sccNum)
{
    if (visited2[start])
        return;

    visited2[start] = true;
    belong[start] = sccNum;

    for (int next : reverse[start])
        SecondDFS(next, sccNum);
}

void FindSCCs(int start)
{
    static int sccNum = 1;

    std::stack<int> s;
    FirstDFS(start, s);

    while (!s.empty())
    {
        int now = s.top();
        s.pop();

        if (!visited2[now])
        {
            SecondDFS(now, sccNum++);
        }
    }
}

int main()
{
    std::fill(belong, belong + MAXINPUT * 2, -1);
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        a = (a < 0 ? Not(-a - 1) : a - 1);
        b = (b < 0 ? Not(-b - 1) : b - 1);

        graph[Not(a)].push_back(b);
        graph[Not(b)].push_back(a);

        reverse[b].push_back(Not(a));
        reverse[a].push_back(Not(b));
    }

    int sccNum = 1;

    std::stack<int> s;
    for (int i = 0; i <= n - 1; ++i)
        FirstDFS(i, s);
    for (int i = Not(0); i <= Not(n - 1); ++i)
        FirstDFS(i, s);

    while (!s.empty())
    {
        int now = s.top();
        s.pop();

        if (!visited2[now])
            SecondDFS(now, sccNum++);
    }

    bool able = true;

    for (int num = 0; num <= n - 1; ++num)
    {
        int oppo = Not(num);
        //printf("num=%d, oppo=%d, belong[num]=%d, belong[oppo]=%d\n", num, oppo, belong[num], belong[oppo]);
        if (belong[num] != -1 && belong[num] == belong[oppo])
        {
            able = false;
            break;
        }
    }

    printf("%d", able ? 1 : 0);

    return 0;
}