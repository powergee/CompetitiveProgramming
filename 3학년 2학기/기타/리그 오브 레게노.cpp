#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::set<std::string> items;
    std::vector<std::pair<std::string, std::string>> edges;
    
    for (int i = 0; i < n; ++i) {
        std::string s1, s2;
        std::cin >> s1 >> s2;
        items.insert(s1);
        items.insert(s2);
        edges.emplace_back(s1, s2);
    }

    int index = 0;
    std::map<std::string, int> itemToIdx;
    std::map<int, std::string> idxToItem;
    for (auto name : items) {
        itemToIdx[name] = index;
        idxToItem[index] = name;
        ++index;
    }

    int itemCount = itemToIdx.size();
    std::vector<std::vector<int>> out(itemCount);
    std::vector<std::vector<int>> in(itemCount);
    for (auto e : edges) {
        int u = itemToIdx[e.first];
        int v = itemToIdx[e.second];
        out[u].push_back(v);
        in[v].push_back(u);
    }

    std::vector<int> q;
    std::vector<std::string> answer;
    std::vector<bool> visited(itemCount, false);
    std::vector<int> prevVisited(itemCount, 0);
    for (int i = 0; i < itemCount; ++i) {
        if (in[i].empty()) {
            q.push_back(i);
        }
    }

    while (!q.empty()) {
        std::vector<int> nextQ;
        for (int idx : q) {
            visited[idx] = true;
            answer.push_back(idxToItem[idx]);
            for (int next : out[idx]) {
                prevVisited[next]++;
                if (prevVisited[next] == in[next].size()) {
                    nextQ.push_back(next);
                }
            }
        }
        std::sort(nextQ.begin(), nextQ.end());
        q = nextQ;
    }

    if (std::all_of(visited.begin(), visited.end(), [](bool v) -> bool { return v; })) {
        for (auto& ans : answer) {
            std::cout << ans << "\n";
        }
    } else {
        std::cout << "-1";
    }

    return 0;
}