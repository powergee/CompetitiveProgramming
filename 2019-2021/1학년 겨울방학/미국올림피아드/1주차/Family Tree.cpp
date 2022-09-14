#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

int GetIndex(const std::string& name);
int FindRoot(int child);
void DFS(int start, int d);
int LCA(int a, int b);
bool FindRelation(const std::string& c1, const std::string& c2, std::string& result);
bool AddMotherStr(int height, std::string& result);
bool AddAuntSisterStr(int height, std::string& result);

int N;
std::string cow1;
std::string cow2;
std::vector<std::vector<int>> graph;
std::vector<int> parent;
std::vector<int> depth;

std::unordered_map<std::string, int> map;
int nextIndex = 0;

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> N;
    graph.resize(N * 2);
    parent.resize(N * 2);
    depth.resize(N * 2);
    std::fill(parent.begin(), parent.end(), -1);

    std::cin >> cow1 >> cow2;

    for (int i = 0; i < N; ++i)
    {
        std::string a, b;
        std::cin >> a >> b;
        int i1 = GetIndex(a), i2 = GetIndex(b);
        graph[i1].push_back(i2);
        parent[i2] = i1;
    }

    std::string result;
    if (!FindRelation(cow1, cow2, result))
        FindRelation(cow2, cow1, result);
    std::cout << result;

    return 0;
}

int GetIndex(const std::string& name)
{
    auto found = map.find(name);
    if (found == map.end())
    {
        map[name] = nextIndex;
        return nextIndex++;
    }
    else
        return found->second;
}

int FindRoot(int child)
{
    if (parent[child] == -1)
        return child;
    else return FindRoot(parent[child]);
}

void DFS(int start, int d)
{
    depth[start] = d;

    for (int next : graph[start])
    {
        DFS(next, d + 1);
        parent[next] = start;
    }
}

int LCA(int a, int b)
{
    int aDep = depth[a];
    int bDep = depth[b];

    if (aDep > bDep)
    {
        std::swap(aDep, bDep);
        std::swap(a, b);
    }

    while (aDep < bDep)
    {
        --bDep;
        b = parent[b];
    }

    while (a != b)
    {
        a = parent[a];
        b = parent[b];
    }

    return a;
}

bool FindRelation(const std::string& c1, const std::string& c2, std::string& result)
{
    int index1 = GetIndex(c1), index2 = GetIndex(c2);
    int root1 = FindRoot(index1), root2 = FindRoot(index2);

    if (root1 == root2)
    {
        DFS(root1, 0);
        int lca = LCA(index1, index2);

        int dist1 = depth[index1] - depth[lca];
        int dist2 = depth[index2] - depth[lca];

        if (dist1 == dist2 && dist1 == 1)
        {
            result = "SIBLINGS";
            return true;
        }
        else if (lca == index2)
        {
            result = c2 + " is the ";
            if (!AddMotherStr(depth[index1] - depth[index2], result))
                return false;
            result += " of " + c1;
            return true;
        }
        else if (dist2 == 1)
        {
            result = c2 + " is the ";
            if (!AddAuntSisterStr(depth[index1] - depth[lca], result))
                return false;
            result += " of " + c1;
            return true;
        }
        else 
        {
            result = "COUSINS";
            return false;
        }
    }
    else
    {
        result = "NOT RELATED";
        return false;
    }
}

bool AddMotherStr(int height, std::string& result)
{
    if (height <= 0)
        return false;
    else if (height == 1)
        result += "mother";
    else if (height == 2)
        result += "grand-mother";
    else
    {
        result += "great-";
        AddMotherStr(height - 1, result);
    }

    return true;
}

bool AddAuntSisterStr(int height, std::string& result)
{
    if (height <= 0)
        return false;
    else if (height == 1)
        result += "sister";
    else if (height == 2)
        result += "aunt";
    else
    {
        result += "great-";
        AddAuntSisterStr(height - 1, result);
    }

    return true;
}