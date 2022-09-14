#include <iostream>
#include <algorithm>

int G, P;
int gi[100001];

int parent[100001];

int Find(int n)
{
    if (parent[n] == n) return n;
    return parent[n] = Find(parent[n]);
}

void Union(int a, int b)
{
    a = Find(a);
    b = Find(b);

    if (a != b) parent[b] = a;
}

int main()
{
    for (int i = 0; i < 100001; ++i)
        parent[i] = i;

    scanf("%d %d", &G, &P);

    for (int i = 0; i < P; ++i)
    {
        scanf("%d", &gi[i]);
    }

    int result = 0;
    for (int i = 0; i < P; ++i)
    {
        int p = Find(gi[i]);

        // 트리가 끝까지 이어졌음. 더이상 연결 불가!
        if (p == 0)
        {
            break;
        }
        else
        {
            parent[p] = p - 1;
            ++result;
        }
    }

    printf("%d", result);

    return 0;
}