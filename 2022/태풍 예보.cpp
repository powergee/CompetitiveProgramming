#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>

using Long = long long;
using Point = std::pair<Long, Long>;

int calcCCW(Point p1, Point p2, Point p3) {
    Long op = p1.first*p2.second + p2.first*p3.second + p3.first*p1.second
            - p1.second*p2.first - p2.second*p3.first - p3.second*p1.first;
    if (op < 0) {
        return 1;
    } else if (op == 0) {
        return 0;
    } else {
        return -1;
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    Long n, k, r, q;
    std::cin >> n >> k >> r >> q;
    
    std::vector<Point> pos(n+1, { -1, -1 });
    for (int i = 0; i < k; ++i) {
        Long day, x, y;
        std::cin >> day >> x >> y;
        pos[day] = { x, y };
    }

    auto start = pos.begin()+1;
    while (start+1 != pos.end()) {
        auto end = std::find_if(start+1, pos.end(), [](auto p) { return p.first != -1; });
        Long dx = end->first - start->first;
        Long dy = end->second - start->second;
        int length = end - start;
        for (auto it = start+1; it != end; ++it) {
            *it = { start->first + (dx/length)*(it-start), start->second + (dy/length)*(it-start) };
        }
        start = end;
    }

    auto p1 = pos[n-1];
    auto p2 = pos[n];
    pos.emplace_back(p2.first + p2.first-p1.first, p2.second + p2.second-p1.second);

    std::vector<std::tuple<int, Long, Long, int>> queries(q);
    std::vector<const char*> answer(q);
    for (int i = 0; i < q; ++i) {
        Long day, x, y;
        std::cin >> day >> x >> y;
        queries[i] = { day, x, y, i };
    }

    std::sort(queries.begin(), queries.end(), [](auto q1, auto q2) { return std::get<0>(q1) < std::get<0>(q2); });

    std::size_t qIdx = 0;
    for (int day = 1; day <= n; ++day) {
        auto [sX, sY] = pos[day];
        while (qIdx < queries.size() && std::get<0>(queries[qIdx]) == day) {
            auto [_, qX, qY, ansIdx] = queries[qIdx++];
            Long dist = (qX-sX)*(qX-sX) + (qY-sY)*(qY-sY);
            Long ccw = calcCCW(pos[day], pos[day+1], { qX, qY });

            if (dist > r*r || ccw == 0) {
                answer[ansIdx] = "gori";
            } else if (ccw > 0) {
                answer[ansIdx] = "unsafe";
            } else {
                answer[ansIdx] = "safe";
            }
        }
    }

    for (const char* ans : answer) {
        std::cout << ans << "\n";
    }

    return 0;
}