#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

std::vector<std::pair<Long, int>> arr;
std::vector<Long> cap;

int main() {
    int n;

    scanf("%d", &n);

    Long capacity = 0;
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        if (val > 0) {
            capacity += val;
            ++answer;
        } else {
            arr.emplace_back(-val, arr.size());
            cap.push_back(capacity);
        }
    }

    std::sort(arr.begin(), arr.end());
    for (auto p : arr) {
        bool allBigger = true;
        for (int i = p.second; i < arr.size(); ++i) {
            if (cap[i] < p.first) {
                allBigger = false;
                break;
            }
        }

        if (allBigger) {
            ++answer;
            for (int i = p.second; i < arr.size(); ++i) {
                cap[i] -= p.first;
            }
        }
    }

    printf("%d", answer);

    return 0;
}