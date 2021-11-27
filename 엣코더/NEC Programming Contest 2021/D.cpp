#include <cstdio>
#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string str;
    std::cin >> str;
    int k;
    std::cin >> k;
    str += ' ';

    auto isPossible = [&](int size) -> bool {
        if (size == 0) {
            return true;
        }

        int xCount = 0, bCount = 0;
        for (int i = 0; i < size; ++i) {
            (str[i] == 'X' ? xCount : bCount)++;
        }

        for (int i = size-1; i < str.size(); ++i) {
            if (bCount <= k) {
                return true;
            }
            (str[i-size+1] == 'X' ? xCount : bCount)--;
            (str[i+1] == 'X' ? xCount : bCount)++;
        }
        return false;
    };

    int left = 0, right = int(str.size())-1;
    while (left+1 < right) {
        int mid = (left+right)/2;
        if (isPossible(mid)) {
            left = mid;
        } else {
            right = mid-1;
        }
    }

    if (isPossible(right)) {
        std::cout << right;
    } else {
        std::cout << left;
    }

    return 0;
}
