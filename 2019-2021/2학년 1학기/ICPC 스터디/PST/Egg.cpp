#include <iostream>
#include <algorithm>
#include <vector>

class Node
{
public:
    int l, r, val;
};

int head[100002];
std::vector<Node> node(2);

void Init(int nidx, int node_st, int node_en)
{
    if (node_st == node_en)
        return;
    int mid = (node_st + node_en) / 2;

    node.push_back({ 0,0,0 });
    node[nidx].l = node.size() - 1;
    Init(node[nidx].l, node_st, mid);

    node.push_back({ 0,0,0 });
    node[nidx].r = node.size() - 1;
    Init(node[nidx].r, mid + 1, node_en);
}

// 이 문제에서는 i가 y의 위치(+1), x가 더해지는 값
void Update(int i, int x, int nidx, int node_st, int node_en) 
{
    if (node_st == node_en)
        return;
    int mid = (node_st + node_en) / 2;

    if (i <= mid) 
    {
        int lidx = node[nidx].l;
        node.push_back({ node[lidx].l, node[lidx].r, node[lidx].val + x });
        node[nidx].l = node.size() - 1;
        Update(i, x, node[nidx].l, node_st, mid);
    }
    else 
    {
        int ridx = node[nidx].r;
        node.push_back({ node[ridx].l, node[ridx].r, node[ridx].val + x });
        node[nidx].r = node.size() - 1;
        Update(i, x, node[nidx].r, mid + 1, node_en);
    }
}

int Query(int i, int j, int nidx, int node_st, int node_en) 
{
    if (j < node_st || i > node_en) 
        return 0;
    else if (i <= node_st && node_en <= j) 
        return node[nidx].val;

    int mid = (node_st + node_en) / 2;
    return Query(i, j, node[nidx].l, node_st, mid) + Query(i, j, node[nidx].r, mid + 1, node_en);
}

int main(void) 
{
    int T;
    scanf("%d", &T);

    while (T--) 
    {
        node.resize(2);
        node[1] = { 0,0,0 };
        std::fill(head, head + 100002, 0);
        head[0] = 1;
        Init(1, 1, 100001);

        int n, m;
        scanf("%d%d", &n, &m);
        std::vector<int> yidx[100002];

        while (n--) 
        {
            int x, y;
            scanf("%d%d", &x, &y);
            x++; y++;
            yidx[x].push_back(y);
        }

        for (int i = 1; i <= 100001; i++) 
        {
            node.push_back({ node[head[i - 1]].l, node[head[i - 1]].r, node[head[i - 1]].val });
            head[i] = node.size() - 1;

            for (auto y : yidx[i]) 
            {
                node[head[i]].val += 1;
                Update(y, 1, head[i], 1, 100001);
            }
        }

        long long tot = 0;

        while (m--) 
        {
            int l, r, b, t;
            scanf("%d%d%d%d", &l, &r, &b, &t);
            l++; r++; b++; t++;
            tot += Query(b, t, head[r], 1, 100001) - Query(b, t, head[l - 1], 1, 100001);
        }
        printf("%lld\n", tot);
    }
}