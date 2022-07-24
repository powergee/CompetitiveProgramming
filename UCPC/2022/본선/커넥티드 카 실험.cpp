#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using Car = std::pair<int, int>;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, s;
    std::cin >> n >> s;

    std::vector<Car> cars(n);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        cars[i].first = x;
    }

    for (int i = 0; i < n; ++i) {
        int h;
        std::cin >> h;
        cars[i].second = h;
    }

    std::queue<int> q;
    std::vector<bool> visited(n, false);
    q.push(s-1);
    visited[s-1] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        int l = cars[curr].first - cars[curr].second;
        int r = cars[curr].first + cars[curr].second;

        auto lit = std::lower_bound(cars.begin(), cars.end(), std::make_pair(l, 0));
        auto rit = std::lower_bound(cars.begin(), cars.end(), std::make_pair(r, 0));
        if (rit == cars.end() || rit->first > r) {
            --rit;
        }
        if (lit <= rit) {
            for (auto it = lit; it <= rit; ++it) {
                int i = it - cars.begin();
                if (visited[i]) {
                    break;
                } else {
                    visited[i] = true;
                    q.push(i);
                }
            }
            for (auto it = rit; it >= lit; --it) {
                int i = it - cars.begin();
                if (visited[i]) {
                    break;
                } else {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            std::cout << i+1 << " ";
        }
    }

    return 0;
}