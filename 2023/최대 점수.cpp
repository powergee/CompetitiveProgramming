#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, s;
    std::cin >> n >> s;
    std::vector<Long> map(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
    }

    auto collect = [&](int start, int diff) -> std::vector<std::pair<Long, Long>> {
        std::vector<std::pair<Long, Long>> right;
        if (0 <= start && start < n) {
            right.emplace_back((map[start] > 0 ? 0 : map[start]), map[start]);
            for (int i = start+diff; 0 <= i && i < n; i += diff) {
                if (map[i] > 0) {
                    right.back().second += map[i];
                } else {
                    if (right.back().second <= 0) {
                        right.back().second += map[i];
                        right.back().first = std::min(right.back().first, right.back().second);
                    } else {
                        right.emplace_back(map[i], map[i]);
                    }
                }
            }
        }
        return right;
    };

    --s;
    auto left = collect(s-1, -1);
    auto right = collect(s+1, 1);

    Long answer = 0;
    size_t lid = 0, rid = 0;
    while (lid < left.size() && rid < right.size()) {
        int stopped = 0;
        if (left[lid].second <= 0) {
            lid = left.size();
        } else if (answer+left[lid].first >= 0) {
            answer += left[lid].second;
            lid++;
        } else {
            stopped++;
        }
        if (right[rid].second <= 0) {
            rid = right.size();
        } else if (answer+right[rid].first >= 0) {
            answer += right[rid].second;
            rid++;
        } else {
            stopped++;
        }
        if (stopped == 2) {
            lid = left.size();
            rid = right.size();
        }
    }
    while (lid < left.size()) {
        if (left[lid].second <= 0) {
            lid = left.size();
        } else if (answer+left[lid].first >= 0) {
            answer += left[lid].second;
            lid++;
        } else {
            break;
        }
    }
    while (rid < right.size()) {
        if (right[rid].second <= 0) {
            rid = right.size();
        } else if (answer+right[rid].first >= 0) {
            answer += right[rid].second;
            rid++;
        } else {
            break;
        }
    }

    std::cout << answer;

    return 0;
}