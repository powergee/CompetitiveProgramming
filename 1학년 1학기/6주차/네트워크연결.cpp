#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Edge
{
public:
    int Start, End, Cost;

    Edge(int s, int e, int c)
    {
        Start = s;
        End = e;
        Cost = c;
    }

    bool operator < (const Edge& e)
    {
        return Cost < e.Cost;
    }
};

int N, M;
vector<Edge> edges;
int root[10001];

int FindRoot(int x)
{
    if (root[x] == x)
        return x;
    
    return root[x] = FindRoot(root[x]);
}

void Union(int x, int y)
{
    x = FindRoot(x);
    y = FindRoot(y);
    root[y] = x;
}

int main()
{
    scanf("%d", &N);
    scanf("%d", &M);

    for (int i = 0; i < M; ++i)
    {
        int s, e, c;
        scanf("%d %d %d", &s, &e, & c);
        edges.push_back(Edge(s, e, c));
    }

    sort(edges.begin(), edges.end());
    for (int i = 1; i < 1001; ++i)
        root[i] = i;

    int sum = 0;
    for (Edge e : edges)
    {
        int root1 = FindRoot(e.Start);
        int root2 = FindRoot(e.End);
        if  (root1 != root2)
        {
            Union(root1, root2);
            sum += e.Cost;
        }
    }

    printf("%d\n", sum);
    return 0;
}