#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
vector<int> tree[10001];
int parent[10001];
int depth[10001];
// depth 저장하는 코드 추가 필요....

void BFS()
{
    queue<pair<int, int>> q;
    q.push(make_pair(1, 0));

    while (!q.empty())
    {
        pair<int, int> now = q.front();
        q.pop();

        parent[now.first] = now.second;

        for (int next : tree[now.first])
        {
            q.push(make_pair(next, now));
        }
    }
}

void Swap(int& a, int& b)
{
    int temp = b;
    b = a;
    a = temp;
}

int LCA(int a, int b)
{
}

int main()
{
    scanf("%d", &N);

    for (--N)
    {
        int start, end;
        scanf("%d %d", &start, &end);
        tree[start].push_back(end);
    }

    BFS();

    scanf("%d", &M);

    for (--M)
    {
        int a, int b;

    }

    return 0;
}