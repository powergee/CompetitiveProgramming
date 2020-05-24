#include <iostream>
#include <unordered_set>
#include <vector>

int n;
int graph[200001];
bool used[200001];
int answer[200001];
std::unordered_set<int> unUsed;

int Next(int except)
{
    for (int ele : unUsed)
    {
        if (except == ele)
            continue;
        else
        {
            unUsed.erase(ele);
            return ele;
        }
    }
 
    return 0;
}

bool FillAnswer(int pos)
{
    if (pos > n)
        return true;

    if (graph[pos] != 0)
    {
        answer[pos] = graph[pos];
        if (FillAnswer(pos + 1))
            return true;
    }
    else
    {
        while (true)
        {
        answer[pos] = Next(pos);
        if (answer[pos] == 0)
            return false;

        if (FillAnswer(pos + 1))
            return true;
        else
            unUsed.insert(pos);
        }
    }

    return false;
}

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", graph + i);

        if (graph[i] != 0)
            used[graph[i]] = true;
    }

    for (int i = 1; i <= n; ++i)
    {
        if (!used[i])
            unUsed.insert(i);
    }

    while (!FillAnswer(0));

    for (int i = 1; i <= n; ++i)
        printf("%d ", answer[i]);

    printf("\n");

    return 0;
}