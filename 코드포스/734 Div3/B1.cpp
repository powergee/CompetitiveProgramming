#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        char str[51];
        scanf("%s", str);
        int n = std::strlen(str);
        int k = 2;

        std::vector<std::vector<int>> posVec(26);
        std::vector<int> answer(n, 0);
        for (int i = 0; i < n; ++i) {
            posVec[str[i]-'a'].push_back(i);
        }

        std::vector<std::vector<int>*> sorted;
        for (int i = 0; i < 26; ++i) {
            if (posVec[i].size() > 0) {
                sorted.push_back(&posVec[i]);
            }
        }
        std::sort(sorted.begin(), sorted.end(), [](std::vector<int>* v1, std::vector<int>* v2) -> bool {
            return v2->size() < v1->size();
        });
        
        int sIdx = 0;
        for (; sIdx < sorted.size(); ++sIdx) {
            auto vPtr = sorted[sIdx];
            if (vPtr->size() >= k) {
                for (int i = 0; i < k; ++i) {
                    answer[vPtr->at(i)] = i+1;
                }
            } else {
                break;
            }
        }

        long long remain = 0;
        for (int i = sIdx; i < sorted.size(); ++i) {
            remain += sorted[i]->size();
        }

        while (remain >= k) {
            for (int i = 0; i < k; ++i) {
                while (sorted[sIdx]->size() == 0) {
                    sIdx++;
                }
                answer[sorted[sIdx]->back()] = i+1;
                sorted[sIdx]->pop_back();
            }
            remain -= k;
        }

        int count = 0;
        for (int ans : answer) {
            if (ans == 1) {
                count++;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}