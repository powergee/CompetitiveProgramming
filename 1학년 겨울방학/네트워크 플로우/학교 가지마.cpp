#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <limits>
#define VERTEX_COUNT 20002

bool map[101][101];

struct Edge
{
    int To, Capacity, Flow;
    Edge* Oppo;

    Edge(int to, int cap) : To(to), Capacity(cap), Flow(0), Oppo(nullptr) {}

    int GetSpare()
    {
        return Capacity - Flow;
    }

    void AddFlow(int add)
    {
        Flow += add;
        Oppo->Flow -= add;
    }
};

std::vector<Edge*> graph[VERTEX_COUNT];
int prev[VERTEX_COUNT];
Edge *path[VERTEX_COUNT];

void AddEdge(int from, int to, int primaryCap, int oppoCap)
{
    Edge* primary = new Edge(to, primaryCap);
    Edge* opposite = new Edge(from, oppoCap);

    primary->Oppo = opposite;
    opposite->Oppo = primary;

    graph[from].push_back(primary);
    graph[to].push_back(opposite);
}

bool FindAugPath(int source, int sink)
{
    std::fill(prev, prev + VERTEX_COUNT, -1);
    std::queue<int> q;
    q.push(source);

    while (!q.empty() && prev[sink] == -1)
    {
        int now = q.front();
        q.pop();

        for (Edge *e : graph[now])
        {
            int next = e->To;

            if (e->GetSpare() > 0 && prev[next] == -1)
            {
                q.push(next);
                prev[next] = now;
                path[next] = e;

                if (next == sink)
                    break;
            }
        }
    }

    if (prev[sink] == -1)
        return false;
    else return true;
}

int EdmondsKarp(int source, int sink)
{
    int result = 0;
    while (FindAugPath(source, sink))
    {
        int flow = INT32_MAX;

        for (int i = sink; i != source; i = prev[i])
            flow = std::min(flow, path[i]->GetSpare());

        for (int i = sink; i != source; i = prev[i])
            path[i]->AddFlow(flow);

        result += flow;
    }

    return result;
}

int In(int num)
{
    return num * 2;
}

int Out(int num)
{
    return num * 2 + 1;
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int height, width;
    std::cin >> height >> width;
    int source = 0, sink = 0;
    std::pair<int, int> sourcePos, sinkPos;

    for (int row = 0; row < height; ++row)
    {
        std::string line;
        std::cin >> line;

        for (int col = 0; col < width; ++col)
        {
            if (line[col] == '#')
                continue;

            map[row][col] = true;
            int index = row * width + col + 1;

            if (line[col] == 'K')
            {
                sourcePos.first = row;
                sourcePos.second = col;
                source = index;
            }

            if (line[col] == 'H')
            {
                sinkPos.first = row;
                sinkPos.second = col;
                sink = index;
            }

            AddEdge(In(index), Out(index), 1, 0);

            if (col - 1 >= 0 && map[row][col - 1])
            {
                AddEdge(Out(index - 1), In(index), INT32_MAX, 0);
                AddEdge(Out(index), In(index - 1), INT32_MAX, 0);
            }

            if (row - 1 >= 0 && map[row - 1][col])
            {
                AddEdge(Out(index - width), In(index), INT32_MAX, 0);
                AddEdge(Out(index), In(index - width), INT32_MAX, 0);
            }
        }
    }

    if ((sourcePos.first - 1 == sinkPos.first && sourcePos.second == sinkPos.second) ||
        (sourcePos.first + 1 == sinkPos.first && sourcePos.second == sinkPos.second) ||
        (sourcePos.first == sinkPos.first && sourcePos.second + 1 == sinkPos.second) ||
        (sourcePos.first == sinkPos.first && sourcePos.second - 1 == sinkPos.second))
        std::cout << "-1";

    else std::cout << EdmondsKarp(Out(source), In(sink));

    return 0;
}