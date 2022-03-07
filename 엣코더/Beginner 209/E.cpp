#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <queue>

enum Verdict { Draw, Win, Lose };

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> edges(n);
    std::map<std::string, int> strToId;
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        std::string begin, end;
        begin = word.substr(0, 3);
        end = word.substr(word.size()-3, 3);
        if (strToId.find(begin) == strToId.end()) {
            strToId[begin] = strToId.size();
        }
        if (strToId.find(end) == strToId.end()) {
            strToId[end] = strToId.size();
        }
        edges[i] = { strToId[begin], strToId[end] };
    }
    
    std::vector<std::vector<int>> graph(strToId.size());
    std::vector<std::vector<int>> reverse(strToId.size());
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
        reverse[v].push_back(u);
    }
    
    std::queue<int> q;
    std::vector<Verdict> verdict(strToId.size(), Draw);
    std::vector<bool> visited(strToId.size(), false);
    std::vector<int> neighWinCount(strToId.size(), 0);

    for (int i = 0; i < strToId.size(); ++i) {
        if (graph[i].empty()) {
            verdict[i] = Lose;
            visited[i] = true;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (verdict[curr] == Win) {
            for (int prev : reverse[curr]) {
                neighWinCount[prev]++;
                if (neighWinCount[prev] == graph[prev].size() && !visited[prev]) {
                    verdict[prev] = Lose;
                    visited[prev] = true;
                    q.push(prev);
                }
            }
        } else if (verdict[curr] == Lose) {
            for (int prev : reverse[curr]) {
                if (!visited[prev]) {
                    verdict[prev] = Win;
                    visited[prev] = true;
                    q.push(prev);
                }
            }
        }
    }

    for (auto e : edges) {
        Verdict oppo = verdict[e.second];
        if (oppo == Draw) {
            printf("Draw\n");
        } else if (oppo == Win) {
            printf("Aoki\n");
        } else {
            printf("Takahashi\n");
        }
    }

    return 0;
}