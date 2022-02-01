#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, c;
    scanf("%d %d", &n, &c);
    
    std::vector<int> house(n);
    std::for_each(house.begin(), house.end(), [](int& v) {scanf("%d", &v);});
    std::sort(house.begin(), house.end());

    auto isPossible = [&](int dist) -> bool {
        int remain = c-1, index = 0;
        while (remain) {
            auto next = std::lower_bound(house.begin()+index, house.end(), house[index]+dist);
            index = next - house.begin();
            if (index < n) {
                --remain;
            } else {
                break;
            }
        }
        return remain == 0;
    };

    int left = 1, right = house.back() - house.front();
    while (left+1 < right) {
        int mid = (left+right) / 2;
        if (isPossible(mid)) {
            left = mid;
        } else {
            right = mid-1;
        }
    }

    int maxDist;
    if (isPossible(right)) {
        maxDist = right;
    } else {
        maxDist = left;
    }

    printf("%d", maxDist);

    return 0;
}