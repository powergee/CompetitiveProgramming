#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

int parent[26];
bool visited[26];
std::vector<int> graph[26];

int Find(int x)
{
    if (x == parent[x])
        return x;

    parent[x] = Find(parent[x]);
    return parent[x];
}

void Union(int x, int y)
{
    int xPar = Find(x);
    int yPar = Find(y);

    parent[xPar] = yPar;
}

void DFS(int start)
{
    visited[start] = true;
    std::cout << (char)(start + 'a');

    for (int next : graph[start])
        if (!visited[next])
            DFS(next);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        for (int i = 0; i < 26; ++i)
        {
            parent[i] = i;
            graph[i].clear();
            visited[i] = false;
        }

        std::string str;
        std::cin >> str;

        std::set<std::pair<char, char>> adj;
        for (int i = 0; i < (int)str.size() - 1; ++i)
        {
            char u = str[i], v = str[i + 1];
            if (u > v)
                std::swap(u, v);
            adj.insert({ u, v });
        }

        bool valid = true;
        for (auto p : adj)
        {
            char u = p.first, v = p.second;
            if (Find(u - 'a') == Find(v - 'a'))
                valid = false;
            else
            {
                graph[u - 'a'].push_back(v - 'a');
                graph[v - 'a'].push_back(u - 'a');

                Union(u - 'a', v - 'a');
            }

            if (!valid) break;
        }

        for (int i = 0; i < 26 && valid; ++i)
            if (graph[i].size() >= 3)
                valid = false;

        if (!valid)
            std::cout << "NO\n";
        else
        {
            std::cout << "YES\n";
            for (int i = 0; i < 26; ++i)
                if (!visited[i] && graph[i].size() < 2)
                    DFS(i);
            std::cout << '\n';
        }
    }

    return 0;
}