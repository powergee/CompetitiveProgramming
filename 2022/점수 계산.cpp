#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    std::map<int, int> count;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        count[v]++;
    }

    int answer = 0;
    std::vector<std::pair<int, int>> countVec(count.begin(), count.end());
    for (int i = 0; i < countVec.size(); ++i) {
        if (countVec[i].second >= 2) {
            int mult = countVec[i].first*countVec[i].first;
            int curr = 0;
            for (char ch : std::to_string(mult)) {
                curr += ch - '0';
            }
            answer = std::max(answer, curr);
        }
        for (int j = i+1; j < countVec.size(); ++j) {
            int mult = countVec[i].first*countVec[j].first;
            int curr = 0;
            for (char ch : std::to_string(mult)) {
                curr += ch - '0';
            }
            answer = std::max(answer, curr);
        }
    }

    std::cout << answer;

    return 0;
}