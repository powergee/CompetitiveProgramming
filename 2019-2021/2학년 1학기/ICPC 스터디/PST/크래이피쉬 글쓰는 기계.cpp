#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

struct Node
{
    char letter;
    int depth = -1;
    bool visited = false;
    int parent[21];
    std::vector<int> nextIndexes;
};

std::vector<Node> nodes;
std::vector<int> callSeq;
std::vector<std::pair<int, int>> getLetter;

void DFS(int start, int depth)
{
    nodes[start].visited = true;
    nodes[start].depth = depth;

    for (int next : nodes[start].nextIndexes)
    {
        if (!nodes[next].visited)
        {
            nodes[next].parent[0] = start;
            DFS(next, depth + 1);
        }
    }
}

int main()
{
    int l;
    std::cin >> l;

    while (l--)
    {
        std::string comm, args;
        std::cin >> comm >> args;

        switch (comm[0])
        {
        case 'T':
            nodes.emplace_back();
            nodes.back().letter = args[0];
            callSeq.push_back((int)nodes.size() - 1);
            if (callSeq.size() >= 2)
            {
                int before = callSeq[callSeq.size() - 2];
                nodes[before].nextIndexes.push_back(callSeq.back());
            }
            break;

        case 'P':
            getLetter.push_back({callSeq.back(), std::stoi(args)});
            break;

        case 'U':
            callSeq.push_back(callSeq[callSeq.size() - 1 - std::stoi(args)]);
            break;
        }
    }

    DFS(0, 0);
    for (int exp = 1; exp < 21; ++exp)
        for (int node = 0; node < (int)nodes.size(); ++node)
            nodes[node].parent[exp] = nodes[nodes[node].parent[exp - 1]].parent[exp - 1];

    for (std::pair<int, int>& p : getLetter)
    {
        int node = p.first;
        int index = p.second;

        int dist = nodes[node].depth - index;
        for (int exp = 20; exp >= 0; --exp)
        {
            if (dist >= (1 << exp))
            {
                node = nodes[node].parent[exp];
                dist -= (1 << exp);
            }
        }

        printf("%c\n", nodes[node].letter);
    }

    return 0;
}