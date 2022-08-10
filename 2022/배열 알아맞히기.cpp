#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>
#include <map>

typedef long long Long;
using QuerySet = std::tuple<int, int, int, Long, Long>;

int askSize() {
    int n;
    std::cin >> n;
    return n;
}

Long query(int p, int q) {
    std::cout << "? " << p << " " << q << "\n";
    std::cout.flush();
    Long res;
    std::cin >> res;
    return res;
}

void answer(int a, int b, int k) {
    std::cout << "! " << a << " " << b << " " << k << "\n";
}

int main() {
    int n = askSize();
    std::mt19937 rng(777);
    std::uniform_int_distribution<int> dist(1, n);
    
    std::vector<QuerySet> queries(100);
    for (int i = 0; i < queries.size(); ++i) {
        std::vector<int> selected;
        selected.reserve(3);
        for (int v = dist(rng); selected.size() < 3; v = dist(rng)) {
            if (std::find(selected.begin(), selected.end(), v) == selected.end()) {
                selected.push_back(v);
            }
        }
        auto [x, y, z] = std::tie(selected[0], selected[1], selected[2]);
        queries[i] = { x, y, z, query(x, y), query(x, z) };
    }

    std::map<Long, int> aCount;
    for (int i = 0; i < queries.size(); ++i) {
        auto [x, y, z, Qxy, Qxz] = queries[i];
        Long aEst = (Qxy-Qxz) / (y-z);
        aCount[aEst]++;
    }
    Long a = std::max_element(aCount.begin(), aCount.end(), [](auto p1, auto p2) { return p1.second < p2.second; })->first;
    
    Long b = INT64_MAX;
    for (int i = 0; i < queries.size(); ++i) {
        auto [x, y, z, Qxy, Qxz] = queries[i];
        Long aEst = (Qxy-Qxz) / (y-z);
        if (aEst == a && ((Qxy - a*(x+y-2)) % 2) == 0) {
            Long bEst = (Qxy - a*(x+y-2)) / 2;
            b = std::min(b, bEst);
        }
    }

    Long k = INT64_MAX;
    for (int i = 0; i < queries.size(); ++i) {
        auto [x, y, z, Qxy, Qxz] = queries[i];
        Long kEst = Qxy - (a*(x-1)+b) - (a*(y-1)+b);
        if (kEst > 0) {
            k = std::min(k, kEst);
        }
        kEst = Qxz - (a*(x-1)+b) - (a*(z-1)+b);
        if (kEst > 0) {
            k = std::min(k, kEst);
        }
    }

    answer(a, b, k);

    return 0;
}