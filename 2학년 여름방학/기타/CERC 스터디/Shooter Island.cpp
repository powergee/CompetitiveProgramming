#include <bits/stdc++.h>

int parent[(52 * 100005)];
int Q, command, x, y, X, Y;
int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
bool destroyed[52][100005];

// disjoint-set: 루트 노드를 찾음
int findRoot(int a)
{
    return parent[a] = (a == parent[a] ? a : findRoot(parent[a]));
}

// disjoint-set: 두 집합을 합침
bool unionNodes(int a, int b)
{
    if (findRoot(a) == findRoot(b))
        return false;

    parent[parent[a]] = parent[b];
    return true;
}

// 두 칸이 모두 파괴된 상태라면 union
void tryToUnion(int x1, int y1, int x2, int y2)
{
    if (destroyed[x1][y1] && destroyed[x2][y2])
        unionNodes(x1*100005+y1, x2*100005+y2);
}

// 주어진 칸을 파괴된 상태로 바꾸고 주변의 파괴된 칸이 있다면 union
void destroyCell(int x, int y)
{
    destroyed[x][y] = true;
    for (int i = 0; i < 4; i++)
        tryToUnion(x, y, x + dx[i], y + dy[i]);
}

// 각 열에 대응하는 DSU를 관리함.
// 이런 DSU를 두는 이유는 어떤 직사각형 영역이 파괴되었을 때,
// 이미 처리한 칸에 대하여 다시 union을 하지 않기 위하여,
// 특정 행보다 위에 있으면서 파괴되어있는 첫번째 칸을 빠르게
// 쿼리하기 위함임.
struct DisjointSet
{
    int parent[100005];
    bool destroyed[100005];

    int findRoot(int a)
    {
        return parent[a] = (a == parent[a] ? a : findRoot(parent[a]));
    }

    void unionNodes(int a, int b)
    {
        if (!destroyed[a] || !destroyed[b] || findRoot(a) == findRoot(b))
            return;

        if (a > b)
            std::swap(a, b);

        parent[parent[a]] = parent[b];
    }

    void destroyCell(int row)
    {
        destroyed[row] = true;
        unionNodes(row, row - 1);
        unionNodes(row, row + 1);
    }

    int findSolidCell(int lower)
    {
        return destroyed[lower] ? findRoot(lower) + 1 : lower;
    }

    DisjointSet()
    {
        std::iota(parent, parent + 100005, 0);
        memset(destroyed, 0, sizeof(destroyed));
    }
} dsuForCols[52];

void destroyRect(int col, int lowerRow, int upperRow)
{
    int x = dsuForCols[col].findSolidCell(lowerRow);
    while (x <= upperRow)
    {
        destroyCell(col, x);
        dsuForCols[col].destroyCell(x);
        x = dsuForCols[col].findSolidCell(x);
    }
}

int main(void)
{
    scanf("%d", &Q);
    std::iota(parent, parent + 52 * 100005, 0);

    for (int i(0); i < Q; i++)
    {
        scanf("%d %d %d %d %d", &command, &x, &y, &X, &Y);

        if (command == 1)
            printf("%d\n", destroyed[x][y] && findRoot((x * 100005 + y)) == findRoot((X * 100005 + Y)));
        else
        {
            if (x > X)
                std::swap(x, X);
            if (y > Y)
                std::swap(y, Y);
            for (int col = x; col <= X; col++)
                destroyRect(col, y, Y);
        }
    }
    return 0;
}
