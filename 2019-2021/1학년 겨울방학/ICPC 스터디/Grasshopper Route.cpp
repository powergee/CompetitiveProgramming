#include <iostream>
#include <set>
#include <stack>

int n, s, t;
std::set<int> tree[100001];
bool onPath[100001];
std::stack<int> pathStack;

bool Init(int start)
{
    bool result = (start == t);
    for (int next : tree[start])
    {
        tree[next].erase(start);
        Init(next);
        result = result || onPath[next];
    }

    onPath[start] = result;
    if (result)
        pathStack.push(start);

    return result;
}

void FindRoute(int start)
{
    printf("%d\n", start);

    for (int child : tree[start])
    {
        if (onPath[child])
            continue;

        for (int grandChild : tree[child])
            FindRoute(grandChild);

        printf("%d\n", child);
    }
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        tree[u].insert(v);
        tree[v].insert(u);
    }

    scanf("%d %d", &s, &t);
    Init(s);

    printf("%d\n", s);
    for (int child : tree[s])
        if (!onPath[child])
            FindRoute(child);

    pathStack.pop();

    while (!pathStack.empty())
    {
        int next = pathStack.top();
        pathStack.pop();

        for (int child : tree[next])
            if (!onPath[child])
                FindRoute(child);

        printf("%d\n", next);
    }

    return 0;
}