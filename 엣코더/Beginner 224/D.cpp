#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

typedef long long Long;

Long getHash(std::vector<int> piece) {
    Long result = 0;
    Long pow = 1;
    for (int i = piece.size()-1; i > 0; --i) {
        result += piece[i] * pow;
        pow *= 10;
    }
    return result;
}

std::vector<int> getPiece(Long hash) {
    std::vector<int> piece(10, 0);
    for (int i = 9; i > 0; --i) {
        piece[i] = hash % 10;
        hash /= 10;
    }
    return piece;
}

bool isValid(std::vector<int> piece) {
    for (int i = 1; i < piece.size()-1; ++i) {
        if (piece[i] != i) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    std::vector<std::vector<int>> graph(10);

    for (int i = 0; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<int> piece(10, 0);
    for (int i = 1; i <= 8; ++i) {
        int p;
        scanf("%d", &p);
        piece[p] = i;
    }

    std::set<Long> visited;
    std::queue<std::pair<int, int>> q;
    q.emplace(getHash(piece), 0);
    visited.insert(q.front().first);
    int answer = -1;

    while (!q.empty()) {
        auto [currHash, currDist] = q.front();
        q.pop();
        
        auto curr = getPiece(currHash);
        if (isValid(curr)) {
            answer = currDist;
            break;
        }

        for (int u = 1; u <= 9; ++u) {
            if (curr[u] != 0) {
                continue;
            }
            for (int v : graph[u]) {
                std::vector<int> next = curr;
                std::swap(next[u], next[v]);
                Long nextHash = getHash(next);
                if (visited.find(nextHash) == visited.end()) {
                    visited.insert(nextHash);
                    q.emplace(nextHash, currDist+1);
                }
            }
        }
    }

    printf("%d", answer);

    return 0;
}