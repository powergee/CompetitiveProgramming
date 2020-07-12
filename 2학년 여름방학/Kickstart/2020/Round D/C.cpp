#include <iostream>
#include <vector>
#include <set>

typedef long long Long;

int n, a, b;
std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> athDes, bthDes;
std::vector<int> athAnc, bthAnc;

void countAthDes(int start)
{
    static std::vector<int> ancStack;

    if ((int)ancStack.size() - a >= 0)
    {
        int athAncNode = ancStack[ancStack.size() - a];
        athDes[athAncNode].push_back(start);
        athAnc[start] = athAncNode;
    }
    ancStack.push_back(start);

    for (int next : graph[start])
        countAthDes(next);

    ancStack.pop_back();
}

void countBthDes(int start)
{
    static std::vector<int> ancStack;

    if ((int)ancStack.size() - b >= 0)
    {
        int bthAncNode = ancStack[ancStack.size() - b];
        bthDes[bthAncNode].push_back(start);
        bthAnc[start] = bthAncNode;
    }
    ancStack.push_back(start);

    for (int next : graph[start])
        countBthDes(next);

    ancStack.pop_back();
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t)
    {
        scanf("%d %d %d", &n, &a, &b);
        graph.clear();
        graph.resize(n);
        athDes.clear();
        athDes.resize(n);
        bthDes.clear();
        bthDes.resize(n);
        athAnc.clear();
        athAnc.resize(n, -1);
        bthAnc.clear();
        bthAnc.resize(n, -1);

        for (int i = 1; i < n; ++i)
        {
            int parent;
            scanf("%d", &parent);
            graph[parent-1].push_back(i);
        }

        countAthDes(0);
        countBthDes(0);

        Long nodeCount = 0;
        int caseCount = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                ++caseCount;
                std::set<int> painted;

                for (int aPos = i; aPos != -1; aPos = athAnc[aPos])
                    painted.insert(aPos);
                
                for (int bPos = j; bPos != -1; bPos = bthAnc[bPos])
                    painted.insert(bPos);
                
                nodeCount += painted.size();
            }
        }

        printf("Case #%d: %lf\n", t, (double)nodeCount / caseCount);
    }

    return 0;
}