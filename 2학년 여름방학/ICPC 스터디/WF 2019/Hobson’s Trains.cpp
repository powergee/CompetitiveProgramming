#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int n, k;
int graph[500001];
std::vector<int> reverse[500001];
bool isRing[500001];
int ringCount[500001];
int kthDesCount[500001];
int answer[500001];

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

void getAnswerForRing(int ring)
{
    int initial = std::min(k+1, ringCount[ring]);
    answer[ring] = initial;
    for (int curr = graph[ring]; curr != ring; curr = graph[curr])
        answer[curr] = initial;
}

void getAnswerForAdjRing(int adjToRing)
{
    int ring = graph[adjToRing];

    if (answer[ring] == 0)
        getAnswerForRing(ring);

    std::vector<int> diff(ringCount[ring], 0);
    std::queue<std::pair<int, int>> q;
    q.push({adjToRing, 1});

    int rightMost = 0;
    while (!q.empty())
    {
        auto now = q.front();
        q.pop();

        if (k - now.second >= ringCount[ring] - 1)
        {
            ++diff[0];
            rightMost = ringCount[ring] - 1;
        }
        else if (now.second <= k)
        {
            ++diff[0];
            --diff[k-now.second+1];
            rightMost = std::max(rightMost, k-now.second+1);
        }
        else break;

        for (int next : reverse[now.first])
            q.push({next, now.second + 1});
    }

    int addition = 0;
    for (int i = 0; i <= rightMost; ++i)
    {
        addition += diff[i];
        answer[ring] += addition;
        ring = graph[ring];
    }
}

void identifyRings(int start)
{
    static bool isInStack[500001];
    static bool visited[500001];

    if (isInStack[start])
    {
        int count = 1;
        isRing[start] = true;
        for (int ring = graph[start]; ring != start; ring = graph[ring])
        {
            isRing[ring] = true;
            ++count;
        }

        ringCount[start] = count;
        for (int ring = graph[start]; ring != start; ring = graph[ring])
            ringCount[ring] = count;

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
            getAnswerForAdjRing(i);
        }
        else if (isRing[i] && answer[i] == 0)
            getAnswerForRing(i);
    }

    for (int i = 1; i <= n; ++i)
        printf("%d\n", answer[i]);

    return 0;
}