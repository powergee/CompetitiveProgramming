#include <iostream>
#include <vector>
#include <queue>
#include <set>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    std::cin >> n >> k;

    std::vector<int> level(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> level[i];
    }

    std::queue<int> pageQueue;
    std::set<std::pair<int, int>> pageSet;
    std::vector<bool> solved(n, false);

    auto addLast = [&]() {
        static int pageEnd = 0;
        if (pageEnd < n) {
            pageQueue.push(pageEnd);
            pageSet.emplace(level[pageEnd], pageEnd);
            ++pageEnd;
        }
    };

    for (int i = 0; i < k; ++i) {
        addLast();
    }

    int answer = 0;
    while (pageQueue.size()) {
        std::vector<int> currSolved;
        int init = pageQueue.front();
        pageQueue.pop();
        solved[init] = true;
        addLast();
        currSolved.push_back(init);

        int cursor = init;
        while (true) {
            auto it = pageSet.lower_bound({level[cursor]+1, 0});
            if (it == pageSet.end()) {
                break;
            }
            auto [clevel, cid] = *it;
            pageSet.erase(it);
            if (solved[cid]) {
                continue;
            }
            solved[cid] = true;
            addLast();
            cursor = cid;
            currSolved.push_back(cid);
        }
        
        while (pageQueue.size() && solved[pageQueue.front()]) {
            pageQueue.pop();
        }
        ++answer;

        for (int v : currSolved) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

    std::cout << answer;

    return 0;
}