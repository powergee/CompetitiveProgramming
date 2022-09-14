#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::unordered_map<std::string, int> prevIdxMap;
    for (int i = 0; i < n; ++i) {
        std::string id;
        std::cin >> id;
        prevIdxMap[id] = i;
    }

    std::vector<int> currIdx;
    for (int i = 0; i < n; ++i) {
        std::string id;
        std::cin >> id;
        currIdx.push_back(prevIdxMap[id]);
    }

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (currIdx[i] > currIdx[j]) {
                ++answer;
                break;
            }
        }
    }

    std::cout << answer;

    return 0;
}