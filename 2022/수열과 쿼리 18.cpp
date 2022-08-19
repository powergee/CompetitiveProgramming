#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;
    const int BLOCK = 1000;

    std::vector<int> arr(n);
    std::vector<std::vector<int>> bucket(n/BLOCK+1); 
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        bucket[i/BLOCK].push_back(arr[i]);
    }

    for (int i = 0; i < bucket.size(); ++i) {
        std::sort(bucket[i].begin(), bucket[i].end());
    }

    int q;
    std::cin >> q;

    while (q--) {
        int op;
        std::cin >> op;

        if (op == 1) {
            int l, r, k;
            std::cin >> l >> r >> k;
            --l; --r;
            int gl = l/BLOCK;
            int gr = r/BLOCK;
            int answer = 0;
            if (gl == gr) {
                for (int i = l; i <= r; ++i) {
                    if (arr[i] > k) {
                        ++answer;
                    }
                }
            } else {
                for (int i = l; i < (gl+1)*BLOCK; ++i) {
                    if (arr[i] > k) {
                        ++answer;
                    }
                }
                for (int i = gl+1; i <= gr-1; ++i) {
                    answer += bucket[i].end() - std::upper_bound(bucket[i].begin(), bucket[i].end(), k);
                }
                for (int i = gr*BLOCK; i <= r; ++i) {
                    if (arr[i] > k) {
                        ++answer;
                    }
                }
            }
            std::cout << answer << "\n";
        } else {
            int i, k;
            std::cin >> i >> k;
            --i;
            int g = i/BLOCK;
            auto it = std::lower_bound(bucket[g].begin(), bucket[g].end(), arr[i]);
            *it = arr[i] = k;
            for (int j = 0; j+1 < bucket[g].size(); ++j) {
                if (bucket[g][j] > bucket[g][j+1]) {
                    std::swap(bucket[g][j], bucket[g][j+1]);
                }
            }
            for (int j = int(bucket[g].size())-1; j >= 1; --j) {
                if (bucket[g][j-1] > bucket[g][j]) {
                    std::swap(bucket[g][j-1], bucket[g][j]);
                }
            }
        }
    }

    return 0;
}