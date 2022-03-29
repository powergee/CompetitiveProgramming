#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>

int main() {
    int n, m, l;
    scanf("%d %d %d", &n, &m, &l);

    std::vector<std::vector<std::pair<int, int>>> forest(n);
    for (int i = 0; i < m; ++i) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        forest[a].emplace_back(b, t);
        forest[b].emplace_back(a, t);
    }

    std::vector<bool> treeVisited(n, false);
    std::vector<bool> iterateVisited(n, false);
    std::vector<int> upperDist(n, 0);
    std::vector<int> distToLeaf(n, 0);

    auto getRadiusOfTree = [&](int root) -> int {
        std::function<void(int)> initDist = [&](int start) {
            treeVisited[start] = true;
            distToLeaf[start] = 0;

            for (auto [next, c] : forest[start]) {
                if (!treeVisited[next]) {
                    initDist(next);
                    distToLeaf[start] = std::max(distToLeaf[start], distToLeaf[next]+c);
                }
            }
        };
        initDist(root);

        int result = INT32_MAX;
        std::function<void(int)> iterateCases = [&](int curr) {
            iterateVisited[curr] = true;
            int currDist = std::max(upperDist[curr], distToLeaf[curr]);
            result = std::min(result, currDist);

            std::vector<std::pair<int, int>> childDists;
            for (auto [next, c] : forest[curr]) {
                if (!iterateVisited[next]) {
                    childDists.emplace_back(c+distToLeaf[next], next);
                }
            }
            std::sort(childDists.begin(), childDists.end(), std::greater<std::pair<int, int>>());
            
            for (auto [next, c] : forest[curr]) {
                if (!iterateVisited[next]) {
                    int siblingMaxDist = 0;
                    if (childDists.size() == 1) {
                        siblingMaxDist = 0;
                    } else if (childDists[0].second == next) {
                        siblingMaxDist = childDists[1].first;
                    } else {
                        siblingMaxDist = childDists[0].first;
                    }
                    upperDist[next] = c + std::max(siblingMaxDist, upperDist[curr]);
                    iterateCases(next);
                }
            }
        };
        upperDist[root] = 0;
        iterateCases(root);
        return result;
    };

    std::vector<int> radius;
    for (int i = 0; i < n; ++i) {
        if (!treeVisited[i]) {
            radius.push_back(getRadiusOfTree(i));
        }
    }

    int diameter = 0;
    for (int i = 0; i < n; ++i) {
        diameter = std::max(diameter, distToLeaf[i] + upperDist[i]);
    }

    if (radius.size() > 1) {
        std::sort(radius.begin(), radius.end());
        std::vector<int> arms(radius.size());
        for (int i = 0; i < radius.size(); ++i) {
            if (i % 2 == 0) {
                arms[i/2] = radius[i];
            } else {
                arms[arms.size()-1 - i/2] = radius[i];
            }
        }
        int maxPrev = arms[0];
        for (int i = 1; i < arms.size(); ++i) {
            diameter = std::max(diameter, maxPrev+l+arms[i]);
            maxPrev = std::max(maxPrev+l, arms[i]);
        }
    }
    printf("%d", diameter);

    return 0;
}