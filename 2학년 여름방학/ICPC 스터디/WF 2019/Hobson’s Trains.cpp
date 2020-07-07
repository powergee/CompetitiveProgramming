#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int n, k;
int graph[500001];
std::vector<int> reverse[500001];

int kthDesCount[500001];
int answer[500001];

bool isRing[500001];
std::vector<int>* nodesOfRing[500001];
int indexInRing[500001];
int diffOfRing[500001];

void countKthDes(int start)
{
    static std::vector<int> ancStack;

    if ((int)ancStack.size() - k >= 0)
    {
        int kthAnc = ancStack[ancStack.size() - k];
        ++kthDesCount[kthAnc];
    }
    ancStack.push_back(start);

    for (int next : reverse[start])
        countKthDes(next);

    ancStack.pop_back();
}

int getAnswerForTree(int node)
{
    int& result = answer[node];
    if (result != 0)
        return result;

    result = 1;
    for (int child : reverse[node])
    {
        result += getAnswerForTree(child);
        result -= kthDesCount[child];
    }

    return result;
}

void initAnswerForRing(int ring)
{
    int initial = std::min(k+1, (int)nodesOfRing[ring]->size());
    answer[ring] = initial;
    for (int curr = graph[ring]; curr != ring; curr = graph[curr])
        answer[curr] += initial;
}

void getDiffOfAdjRing(int adjToRing)
{
    int ring = graph[adjToRing];
    std::vector<int>* nodes = nodesOfRing[ring];
    int count = (int)nodes->size();

    std::queue<std::pair<int, int>> q;
    q.push({adjToRing, 1});

    while (!q.empty())
    {
        auto now = q.front();
        q.pop();

        if (k - now.second >= count - 1)
        {
            ++answer[(*nodes)[0]];
        }
        else if (now.second <= k)
        {
            ++diffOfRing[ring];
            //--diff[k-now.second+1];
            int actualEndPoint = (indexInRing[ring] + k-now.second+1) % count;
            --diffOfRing[(*nodes)[actualEndPoint]];

            if (ring == 0 || (actualEndPoint != 0 && actualEndPoint < ring))
                ++answer[(*nodes)[0]];
        }
        else break;

        for (int next : reverse[now.first])
            q.push({next, now.second + 1});
    }
}

void applyDiffOfRing(int ring)
{
    bool applied[500001];

    if (applied[ring])
        return;

    std::vector<int>* nodes = nodesOfRing[ring];
    for (int node : *nodes)
        applied[node] = true;
    
    int prev = (*nodes)[0];
    for (int current = graph[ring]; current != ring; current = graph[current])
    {
        answer[current] = answer[prev] + diffOfRing[current];
        prev = current;
    }
}

void identifyRings(int start)
{
    static bool isInStack[500001];
    static bool visited[500001];

    if (isInStack[start])
    {
        std::vector<int>* nodes = new std::vector<int>;
        int index = 0;

        isRing[start] = true;
        nodes->push_back(start);
        nodesOfRing[start] = nodes;
        indexInRing[start] = index++;
        int count = 1;
        for (int ring = graph[start]; ring != start; ring = graph[ring])
        {
            isRing[ring] = true;
            nodes->push_back(ring);
            nodesOfRing[ring] = nodes;
            indexInRing[ring] = index++;
            ++count;
        }

        return;
    }

    if (visited[start])
        return;

    isInStack[start] = true;
    visited[start] = true;

    identifyRings(graph[start]);

    isInStack[start] = false;
}

int main()
{
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", graph + i);
        reverse[graph[i]].push_back(i);
    }

    for (int i = 1; i <= n; ++i)
        identifyRings(i);

    for (int i = 1; i <= n; ++i)
    {
        if (!isRing[i] && isRing[graph[i]])
        {
            countKthDes(i);
            getAnswerForTree(i);
            getDiffOfAdjRing(i);
        }
        else if (isRing[i] && answer[i] == 0)
            initAnswerForRing(i);
    }

    for (int i = 1; i <= n; ++i)
        if (isRing[i])
            applyDiffOfRing(i);

    for (int i = 1; i <= n; ++i)
        printf("%d\n", answer[i]);

    return 0;
}