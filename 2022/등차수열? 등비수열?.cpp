#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#define removeIfEmpty(cont, key) if (cont[key] == 0) { cont.erase(key); }

typedef long long Long;
using Fraction = std::pair<Long, Long>;

Fraction getFraction(Long num, Long den) {
    Long gcd = std::gcd(num, den);
    return { num/gcd, den/gcd };
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<Long> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::map<Long, int> diff;
    std::map<Fraction, int> ratio;

    for (int i = 0; i+1 < n; ++i) {
        diff[arr[i+1]-arr[i]]++;
        ratio[getFraction(arr[i+1], arr[i])]++;
    }

    auto insert = [&](int center) {
        if (center > 0) {
            diff[arr[center]-arr[center-1]]++;
            ratio[getFraction(arr[center], arr[center-1])]++;
        }
        if (center+1 < n) {
            diff[arr[center+1]-arr[center]]++;
            ratio[getFraction(arr[center+1], arr[center])]++;
        }
    };

    auto remove = [&](int center) {
        if (center > 0) {
            diff[arr[center]-arr[center-1]]--;
            ratio[getFraction(arr[center], arr[center-1])]--;
        }
        if (center+1 < n) {
            diff[arr[center+1]-arr[center]]--;
            ratio[getFraction(arr[center+1], arr[center])]--;
        }
        
        removeIfEmpty(diff, arr[center]-arr[center-1])
        removeIfEmpty(diff, arr[center+1]-arr[center])
        removeIfEmpty(ratio, getFraction(arr[center], arr[center-1]))
        removeIfEmpty(ratio, getFraction(arr[center+1], arr[center]))
    };

    while (m--) {
        Long i, x;
        std::cin >> i >> x;
        --i;
        remove(i);
        arr[i] = x;
        insert(i);

        if (diff.size() == 1 && diff.begin()->first > 0) {
            std::cout << "+\n";
        } else if (ratio.size() == 1 && ratio.begin()->first.second == 1) {
            std::cout << "*\n";
        } else {
            std::cout << "?\n";
        }
    }

    return 0;
}