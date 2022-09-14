#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>

struct Cow {
    int weight, pos;
    bool right;
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, l;
    std::cin >> n >> l;
    std::vector<Cow> cow(n);
    std::vector<int> left, right;

    int totalWeight = 0;
    for (int i = 0; i < n; ++i) {
        int w, x, d;
        std::cin >> w >> x >> d;
        cow[i] = { w, x, d==1 };
        totalWeight += w;
        (cow[i].right ? right : left).push_back(cow[i].pos);
    }
    std::sort(cow.begin(), cow.end(), [](const Cow& c1, const Cow& c2) { return c1.pos < c2.pos; });
    std::sort(left.begin(), left.end(), [](int p1, int p2) { return p1 > p2; });
    std::sort(right.begin(), right.end(), [](int p1, int p2) { return p1 < p2; });

    std::map<int, std::vector<Cow>> arriveHistory;
    std::deque<Cow> cowDeque(cow.begin(), cow.end());
    for (int i = 0; i < n; ++i) {
        int time = cow[i].right ? l-cow[i].pos : cow[i].pos;
        arriveHistory[time].push_back(cow[i]);
    }

    int endTime = 0, weightSum = 0;
    for (const auto& [time, cows] : arriveHistory) {
        for (const Cow& c : cows) {
            if (c.right) {
                weightSum += cowDeque.back().weight;
                cowDeque.pop_back();
            } else {
                weightSum += cowDeque.front().weight;
                cowDeque.pop_front();
            }
        }
        endTime = time;
        if (2*weightSum >= totalWeight) {
            break;
        }
    }

    long long meetings = 0;
    for (const auto& [time, cows] : arriveHistory) {
        for (const Cow& c : cows) {
            if (c.right) {
                int reachable = c.pos + endTime*2;
                auto it1 = std::lower_bound(left.begin(), left.end(), c.pos, std::greater<int>());
                auto it2 = std::lower_bound(left.begin(), left.end(), reachable, std::greater<int>());
                meetings += it1 - it2;
            } else {
                int reachable = c.pos - endTime*2;
                auto it1 = std::lower_bound(right.begin(), right.end(), c.pos, std::less<int>());
                auto it2 = std::lower_bound(right.begin(), right.end(), reachable, std::less<int>());
                meetings += it1 - it2;
            }
        }
    }

    std::cout << meetings / 2 << "\n";
    
    return 0;
}