#include <iostream>
#include <deque>

int arr[5000000];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, l;
    std::deque<std::pair<int, int>> d;
    std::cin >> n >> l;

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    for (int i = 0; i < n; ++i) {
        while (!d.empty() && arr[i] <= d.back().first) {
            d.pop_back();
        }
        while (!d.empty() && d.front().second <= i-l) {
            d.pop_front();
        }

        d.emplace_back(arr[i], i);
        std::cout << d.front().first << " ";
    }

    return 0;
}