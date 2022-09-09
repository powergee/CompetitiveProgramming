#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    Long answer = 0;
    for (int e = 0; e <= 30; ++e) {
        std::vector<int> segLength, slOddSum {0}, slEvenSum {0};
        segLength.reserve(n);
        slOddSum.reserve(n+1);
        slEvenSum.reserve(n+1);
        int lastOne = -1;

        for (int i = 0; i < n; ++i) {
            if (arr[i] & (1<<e)) {
                int newLength = i - lastOne;
                segLength.push_back(newLength);
                slOddSum.push_back(slOddSum.back() + (((segLength.size()-1) % 2) ? newLength : 0));
                slEvenSum.push_back(slEvenSum.back() + (((segLength.size()-1) % 2) ? 0 : newLength));
                lastOne = i;
            }
            answer += ((segLength.size() % 2) ? slEvenSum.back() : slOddSum.back()) * (1LL << e);
        }
    }

    std::cout << answer << "\n";

    return 0;
}